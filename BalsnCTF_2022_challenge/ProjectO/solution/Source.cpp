#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <string>
#include "message.pb.h"
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <winsock2.h>
#include <io.h>
#include <fcntl.h>
#include <queue>
#include <Wincrypt.h>
#include <vector>
#include <algorithm>
#include <fstream>

#pragma comment(lib,"libprotobuf.lib")
#pragma comment(lib,"libprotobuf-lite.lib")
#pragma comment(lib,"libprotoc.lib")
#pragma comment(lib,"ws2_32.lib")
#define NS(x)  new string(x)
#define INVALID_POINT POINT{-1,-1}

using namespace std;

POINT direction[4] = { {0,-1},{0,1},{-1,0},{1,0} };
int inputSeq = 0;
constexpr int finalLevel = 10;
HCRYPTPROV hCryptProv;
BYTE pbData[4];

enum MODULE {
    ECHO_MODULE = 1,
    INFO_MODULE,
    AUTH_MODULE = 100,
    TEXT_MODULE,
    GAME_MODULE,
};
enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
enum INFO {
    PLAYER_INFO,
    MAP_INFO,
    MISC_INFO
};

enum STATUS {
    SOK,
    SERROR
};

void sendResponse(int status, int* iData, vector<POINT>* points, string* bData);
map <string, string> users = {
        {"O5-1", "v/Xz)9ZNNMT9M"},
        {"O5-2", "sh4`gwXomkT)."},
        {"O5-3", "{97[1$,U9Oj=e"},
        {"O5-4", "C$.h;WLb5Y?z;"},
        {"O5-5", "6qbzZSU\"8o1x ^ "},
};
POINT operator +(POINT& a, POINT& b)
{
    return { a.x + b.x, a.y + b.y };
}
bool operator <(const POINT& a, const POINT& b)
{
    return (a.x < b.x) && (a.y < b.y);
}
bool operator ==(POINT a, POINT b)
{
    return (a.x == b.x) && (a.y == b.y);
}
bool operator !=(POINT a, POINT b)
{
    return !(a == b);
}

class Map {
    int width;
    int height;

    vector<vector<char>> map;
    vector<POINT> available;
public:
    Map(int width, int height) {
        this->width = width;
        this->height = height;
        map.clear();
        for (int r = 0; r < height; r++) {
            vector<char> row;
            for (int c = 0; c < width; c++) {
                row.push_back('\x00');
            }
            map.push_back(row);
        }
        genMap();
    }
    bool isRoad(POINT pos) {
        return map[pos.y][pos.x] == '\x01';
    }
    void setRoad(POINT pos) {
        map[pos.y][pos.x] = '\x01';
    }
    bool onBoarder(POINT pos) {
        return pos.y == 0 || pos.x == 0 || pos.y == height - 1 || pos.x == width - 1;
    }
    POINT spawn(bool reverse) {
        if (reverse) {
            for (int i = height - 2; i > 0 ; i--) {
                for (int j = width - 2; j > 0; j--) {
                    if (isRoad({ j,i })) {
                        available.erase(find(available.begin(), available.end(), POINT{ j, i }));
                        return { j,i };
                    }
                }
            }
        }
        else {
            for (int i = 1; i < height - 1; i++) {
                for (int j = 1; j < width - 1; j++) {
                    if (isRoad({ j,i })) {
                        available.erase(find(available.begin(), available.end(), POINT{ j, i }));
                        return { j,i };
                    }
                }
            }
        }
    }
    POINT randomSpawn() {
        if (available.size()) {
            int idx = rand() % available.size();
            auto result = available[idx];
            available.erase(available.begin() + idx);
            return result;
        }
        else {
            return INVALID_POINT;
        }
    }
    void genMap() {
        std::queue<POINT> nextPoint;
        POINT source = { (rand() % (width - 1)) + 1 , (rand() % (height - 1)) + 1};
        while (onBoarder(source)) {
            source = { (rand() % (width - 1)) + 1, (rand() % (height - 1)) + 1 };
        }
        nextPoint.push(source);
        while (!nextPoint.empty())
        {
            POINT cur = nextPoint.front();
            nextPoint.pop();
            if (isRoad(cur))
                continue;
            if (!(rand() % 3)) {
                nextPoint.push(cur);
                continue;
            }
            int sum = 0;
            for (int d = 0; d < 4; d++) {
                if (isRoad(cur + direction[d])) {
                    sum += 1;
                }
            }
            if (sum > 1) {
                continue;
            }
            setRoad(cur);
            available.push_back(cur);
            int base = rand();

            for (int d = 0; d < 4; d++) {
                POINT  neighbor = cur + direction[(base + d) % 4];
                if (!isRoad(neighbor) && !onBoarder(neighbor)) {
                    nextPoint.push(neighbor);
                }
            }
        }
    }
    string showMap() {
        string mapStr = "";
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                mapStr += map[y][x];
            }
        }
        return mapStr;
    }
    const vector<vector<char>>& getMap() {
        return map;
    }
    int getHeight() {
        return this->height;
    }
    int getWidth() {
        return this->width;
    }
};
class Player {
    int exp;
    POINT pos;
public:
    Player(POINT pos) {
        this->pos = pos;
        this->exp = 0;
    }
    POINT getPos() {
        return this->pos;
    }
    void setPos(POINT pos) {
        this->pos = pos;
    }
    int getExp() {
        return exp;
    }
    void incExp() {
        this->exp++;
    }
};
class Game {
private:
    int level;
    unsigned int tick;
    int width;
    int height;
    int mcbEnemy;
    int expBound;
    int quota;
    Map* map;
    Player* player;
    vector<POINT> enemies;
    POINT portal;
    bool destroy;
public:
    Game(int width, int height, int cbEnemy) {
        this->level = 0;
        this->enemies.clear();
        this->tick = 0;
        this->destroy = false;
        this->height = height;
        this->width = width;
        this->mcbEnemy = cbEnemy;
        this->quota = finalLevel*2;
        this->expBound = cbEnemy/10.0 * 7 * finalLevel;
        map = new Map(width, height);
        player = new Player(map->spawn(false));
        portal = map->spawn(true);
        spawnEnemies(cbEnemy);
    }
    ~Game() {
        delete map;
        delete player;
    }
    Player* getPlayer() {
        return this->player;
    }

    void movePlayer(DIRECTION dir) {
        auto pos = player->getPos();
        POINT newPos = pos + direction[dir];
        if (map->isRoad(newPos) ) {
            player->setPos(newPos);
        }
    }
    POINT getPortal() {
        return this->portal;
    }
    string showMap() {
        if (quota) {
            quota--;
            return this->map->showMap();
        }
        else {
            return "Too many query";
        }
    }
    vector<POINT> getEnemies() {
        return this->enemies;
    }
    POINT getMapSize() {
        return { this->map->getWidth(), this->map->getHeight() };
    }
    void gameTick() {
        if(this->destroy)
            return;
        if (!(++tick % 3)) {
            auto pos = player->getPos();
            for (int dir = 0; dir < 4; dir++) {
                POINT neighbor = pos + direction[dir];
                if (map->isRoad(neighbor) && find(enemies.begin(), enemies.end(), neighbor) != enemies.end()) {
                    this->destroy = true;
                }
            }
        }
        auto kill = find(enemies.begin(), enemies.end(), player->getPos());
        if (kill != enemies.end()) {
            player->incExp();
            enemies.erase(kill);
        }
        if (player->getPos() == portal) {
            if ( ++level != finalLevel) {
                if (map) delete map;
                map = new Map(width, height);
                player->setPos(map->spawn(false));
                portal = map->spawn(true);
                spawnEnemies(this->mcbEnemy);
            }
            else {
                if (player->getExp() >= this->expBound) {
                    ifstream flagFile("flag.txt", ios::in);
                    if(flagFile.is_open()){
                        string flag;
                        flagFile >> flag;
                        sendResponse(SOK, nullptr, nullptr, &flag);
                    }

                }
                this->destroy = true;
            }
            
        }
    }
    int getExpBound() {
        return this->expBound;
    }
    void spawnEnemies(int cbEnemy) {
        this->enemies.clear();
        POINT enemy;
        while (cbEnemy--) {
            if ((enemy = map->randomSpawn()) == INVALID_POINT) {
                break;
            }
            enemies.push_back(enemy);
        }
    }
    bool isGameOver() {
        return this->destroy;
    }
};
class Status {
private:
    string currentUser;
    Game* pGame;
public:
    Status() {
        currentUser = "";
        pGame = nullptr;
    }
    ~Status() {
        if (pGame) {
            delete pGame;
        }
    }
    bool inline isLogin() {
        return currentUser != "";
    }
    void login(string username) {
        currentUser = username;
    }
    void logout() {
        currentUser = "";
    }
    const string& getUsername() {
        return currentUser;
    }
    void newGame(int width, int height, int cbEnemy) {
        cleanGame();
        pGame = new Game(width, height, cbEnemy);
    }
    void cleanGame() {
        if (pGame) {
            delete pGame;
            pGame = nullptr;
        }
    }
    Game* getGame() {
        return this->pGame;
    }
};
Status status;

class Module {
protected:
    bool needAuth = false;
public:
    Module(bool needAuth) { this->needAuth = needAuth; }
    virtual void handler(balsn::Request& request) {
    };
    virtual void parseResponse(pair<char*, int> data) {
        for (int i = 0; i < data.second; i++)
            printf("%02hhx ", data.first[i]);
        cout << endl;
    };
    virtual bool authentication() {
        return (!needAuth) || (status.isLogin());
    }
    virtual bool authorization(){
        return true;
    }
};
class AuthModule : public Module {
public:
    AuthModule(bool na) : Module(na) {}
    void handler(balsn::Request& request) override {
        int op = request.command();
        switch (op) {
        case 1: //login
        {
            balsn::Auth auth;
            if (request.has_data()) {
                auth.ParseFromString(request.data());
                login(auth.username(), auth.password());
            }
            break;
        }
        case 2: //logout
            logout();
            break;
        }
    }
    void inline login(string uname, string passwd) {
        auto user = users.find(uname);
        if (user != users.end() && user->second == passwd) {
            status.logout();
            status.cleanGame();
            status.login(uname);
            string response = string("Success, you are ") + status.getUsername();
            sendResponse(SOK, nullptr, nullptr, &response);
        }
        else {
            sendResponse(SERROR, nullptr, nullptr, NS("Fail"));
        }
    }
    void inline logout() {
        if (status.isLogin()) {
            string response = string("Success, bye~ ") + status.getUsername();
            sendResponse(SOK, nullptr, nullptr, &response);
            status.logout();
            status.cleanGame();
        }
        else {
            sendResponse(SERROR, nullptr, nullptr, NS("Fail"));
        }
    }
};
class GameModule : public Module {
public:
    GameModule(bool na) : Module(na) {};
    void handler(balsn::Request& request) override {
        int op = request.command();
        if(op == 1){
            sendResponse(SOK, nullptr, nullptr, NS("Game Start!"));
            status.newGame(80, 30, 10);
        }
        else if (status.getGame() && !status.getGame()->isGameOver()) {
            if (op == 2) {
                controlHandler(request);
            }
            else if (op == 3) {
                infoHandler(request);
            }
        }
        else {
            sendResponse(SERROR, nullptr, nullptr, NS("Game is not ready..."));
            exit(0);
        }
    }
    void controlHandler(balsn::Request& request) {
        balsn::Control control;
        if (request.has_data() && control.ParseFromString(request.data())) {
            DIRECTION direction = (DIRECTION)control.direction();
            switch (direction) {
            case UP:
            case DOWN:
            case LEFT:
            case RIGHT:
                status.getGame()->movePlayer(direction);
                status.getGame()->gameTick();
                break;
            }
        }
        else {
            sendResponse(SERROR, nullptr, nullptr, NS("Fail"));
        }
    }
    void infoHandler(balsn::Request& request) {
        balsn::Info info;
        if (request.has_data() && info.ParseFromString(request.data())) {
            int which = info.which();
            if (which == PLAYER_INFO)
            {
                switch (info.what()) {
                case 1:{
                    int exp = status.getGame()->getPlayer()->getExp();
                    sendResponse(SOK, &exp, nullptr, nullptr);
                    break;
                }
                case 2:
                    vector<POINT> pos({ status.getGame()->getPlayer()->getPos() });
                    sendResponse(SOK, nullptr, &pos, nullptr);
                    break;
                }
            }
            else if (which == MAP_INFO) {
                switch (info.what()) {
                case 1: {
                    string map = status.getGame()->showMap();
                    sendResponse(SOK, nullptr, nullptr, &map);
                    break;
                }case 2: {
                    vector<POINT> pos({ status.getGame()->getPortal() });
                    sendResponse(SOK, nullptr, &pos, nullptr);
                    break;
                }case 3: {
                    vector<POINT> enemies = status.getGame()->getEnemies();
                    sendResponse(SOK, nullptr, &enemies, nullptr);
                    break;
                }case 4: {
                    vector<POINT> size{ status.getGame()->getMapSize() };
                    sendResponse(SOK, nullptr, &size, nullptr);
                }
                }
            }
            else if (which == MISC_INFO) {
                switch (info.what()) {
                case 1: {
                    int fl = finalLevel;
                    sendResponse(SOK, &fl, nullptr, nullptr);
                    break;
                }
                case 2:
                    int expBound = status.getGame()->getExpBound();
                    sendResponse(SOK, &expBound, nullptr, nullptr);
                    break;
                }
            }
        }
        else {
            sendResponse(SERROR, nullptr, nullptr, NS("Fail"));
        }
    }
    bool authorization() override {
        return status.getUsername() == "O5-5";
    }
};
class EchoModule : public Module {
public:
    EchoModule(bool na) : Module(na) {}
    void handler(balsn::Request& request) override {
        int op = request.command();
        if (op == 1) {
            string raw = request.SerializeAsString();
            sendResponse(SOK, nullptr, nullptr, &raw);
        }
    }
};
bool initChallenge(DWORD sleepMs) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    _setmode(_fileno(stdout), O_BINARY);
    _setmode(_fileno(stdin), O_BINARY);
    std::cout.setf(std::ios::unitbuf);
    if (!CryptAcquireContext(&hCryptProv, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        sendResponse(SERROR, nullptr, nullptr, NS("[!] CryptAcquireContext failed"));
        return false;
    }
    if (!CryptGenRandom(hCryptProv, 4, pbData)) {
        sendResponse(SERROR, nullptr, nullptr, NS("[!] CryptGenRandom failed"));
        return false;
    }
    srand(*(int*)pbData);
    sendResponse(SOK, nullptr, nullptr, NS("Hello from ProjectO v0.01"));
    return true;
}
//lazy, no template
void sendResponse(int status, int* iData, vector<POINT>* points, string* bData) {
    balsn::Response response;
    response.set_status(status);
    if(iData) response.set_idata(*iData);
    if(bData) response.set_bdata(*bData);
    if(points){
        for (auto point : *points) {
            balsn::Point* pdata = response.add_pdata();
            pdata->set_x(point.x);
            pdata->set_y(point.y);
        }
    }
    string raw = response.SerializeAsString();
    char size[4];
    *(int*)size = raw.size();
    cout.write(size, 4);
    cout << raw;
}
int main(int argc, char** argv) {
    if (!initChallenge(3000)) {
        return -1;
    }
    unordered_map <MODULE, shared_ptr<Module>> modules = {
        {ECHO_MODULE, shared_ptr<Module>(new EchoModule(false))},
        {AUTH_MODULE, shared_ptr<Module>(new AuthModule(false))},
        {GAME_MODULE, shared_ptr<Module>(new GameModule(true))},
    };
    
    unsigned int bufSize = 0;
    unsigned int curBufSize = 0x100;
    char* buffer = new char[curBufSize] {0};

    while (true){
        if (!cin.read((char*)&bufSize, 4)) break;
        if (bufSize > curBufSize) break;
        if (!cin.read(buffer, bufSize)) break;
        balsn::Request request;
        if (request.ParseFromArray(buffer, bufSize)) {
            if (auto it = modules.find((MODULE)request.module()); it != modules.end()) {
                auto module = it->second;
                if (module->authentication() && module->authorization()) {
                    module->handler(request);
                }
                else {
                    sendResponse(SERROR, nullptr, nullptr, NS("Permission denied"));
                }
            }
            else {
                sendResponse(SERROR, nullptr, nullptr, NS("That's nonsense"));
            }
        }
    }
    delete[] buffer;
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

