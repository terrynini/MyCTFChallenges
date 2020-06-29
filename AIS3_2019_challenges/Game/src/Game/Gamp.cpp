#include "Game.h"
#include "TextureLoader.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "SDL_ttf.h"
#include "FlagData.h"
#include <string>
#include <cstdlib>
#include <ctime>
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;
std::vector<ColliderComponent*> Game::colliders;
std::vector<Entity*> Game::flags;
std::vector<Entity*> Game::bullets;
auto& player(manager.addEntity());
char Actor[] = { 22, 4, 4, 18, 3, 4, 88, 54, 20, 3, 24, 5, 68, 89, 7, 25, 16 };
char Monster[] = { 22, 4, 4, 18, 3, 4, 88, 58, 24, 25, 4, 3, 18, 5, 89, 7, 25, 16 };
TTF_Font* Font;
SDL_Color White;
int NOW = 0;
int stage = 0;

inline void decode(char* a, char* b, int size)
{
	for (int i = 0; i < size; i++)
		a[i] = b[i] ^ 0x77;
}

enum groupLabels : std::size_t 
{
	groupMap,
	groupPlayers,
	groupFlags,
	groupBullet,
groupColliders
};

Game::Game()
{};
Game::~Game()
{};
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = SDL_WINDOW_SHOWN;
	if (fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "INIT FAIL" << std::endl;
		isRunning = false;
	}
	else
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}

	Map::LoadMap( W_WIDTH / 48 + 1, W_HEIGHT / 48 + 1);
	char temp[18] = { 0 };
	decode(temp, Actor,17);
	player.addComponent<TransformComponent>(W_WIDTH / 2, W_HEIGHT - 48 * 2);
	player.addComponent<SpriteComponent>(temp, true, 300);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("");
	player.addGroup(groupPlayers);

	stage = 0;
	flagDelay = 0;
	point = 0;

	TTF_Init();
	Font = TTF_OpenFont("assets/Rationale-Regular.ttf", 72);
	White = { 255,255,255 };
	srand(time(0));

}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
void Game::update()
{
	manager.refresh();
	manager.update();

	bool aa = false;
	for (auto bu = bullets.begin(); bu != bullets.end();)
	{
		if ((*bu)->getComponent<TransformComponent>().position.y == 0)
		{
			(*bu)->delGroup(groupBullet);
			(*bu)->destroy();
			bu = bullets.erase(bu);
			continue;
		}
		for (auto en = flags.begin(); en != flags.end(); )
		{
			if (Collision::AABB((*bu)->getComponent<ColliderComponent>().collider
				, (*en)->getComponent<ColliderComponent>().collider))
			{
				(*bu)->delGroup(groupBullet);
				(*bu)->destroy();
				(*en)->delGroup(groupFlags);
				(*en)->destroy();
				(*en)->getComponent<FlagComponent>().Draw();
				bu = bullets.erase(bu);
				en = flags.erase(en);
				point++;
				aa = true;
				break;
			}
			else
			{
				en++;
			}
		}
		if (!aa) {
			bu++;
		}
		aa = false;
	}
	for (auto en = flags.begin(); en != flags.end(); )
	{
		if ((*en)->getComponent<TransformComponent>().position.y == W_HEIGHT - 47)
		{
			(*en)->delGroup(groupFlags);
			(*en)->destroy();
			en = flags.erase(en);
		}
		else
		{
			en++;
		}
		
	}
	if (flagDelay == 0)
	{
		if (flags.size() < FLAG_MAX && NOW < 225 && stage<MAX_STAGE)
		{
			char p[19] = { 0 };
			float speeed = stage > 3 ? 1.1 : 0.1;
			decode(p, Monster, 18);
			Entity *temp = &manager.addEntity();
			temp->addComponent<TransformComponent>(rand()%W_WIDTH,0);
			temp->getComponent<TransformComponent>().setVelocity(0, speeed);
			temp->addComponent<SpriteComponent>(p, true, 100);
			temp->getComponent<SpriteComponent>().Play("walks");
			temp->addComponent<ColliderComponent>("");
			temp->addComponent<FlagComponent>(flag[stage][NOW].x, flag[stage][NOW].y, flag[stage][NOW].b);
			temp->addGroup(groupFlags);
			NOW++;
			if (NOW == 225 && stage < MAX_STAGE)
			{
				NOW = 0;
				stage++;
			}

			Game::flags.emplace_back(temp);
		}
		flagDelay = FLAG_DELAY;
	}
	else{
		flagDelay--;
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& bullet(manager.getGroup(groupBullet));
auto& enemies(manager.getGroup(groupFlags));

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles) { t->render(); }
	for (auto& p : players) { p->render(); }
	for (auto& e : enemies) { e->render(); }
	for (auto&b : bullet) { b->render(); }

	std::string msg = "Score:" + std::to_string(point);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font,msg.c_str(), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = W_WIDTH- surfaceMessage->w;  //controls the rect's x coordinate 
	Message_rect.y = W_HEIGHT- surfaceMessage->h; // controls the rect's y coordinte
	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}
bool Game::running()
{
	return isRunning;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 48, 48, id);
	tile.addGroup(groupMap);
}

void Game::DelTile(float x, float y)
{
	for (auto t = tiles.begin() ; t != tiles.end() ; t++)
	{
		if ((*t)->getComponent<TileComponent>().transform->position.x == x &&
			(*t)->getComponent<TileComponent>().transform->position.y == y)
		{
			(*t)->destroy();
			(*t)->delGroup(groupMap);
			tiles.erase(t);
			break;
		}
	}
}

void Game::addBullet(float x, float y)
{
	Entity* temp = &manager.addEntity();
	temp->addComponent<TransformComponent>(x, y);
	temp->getComponent<TransformComponent>().setVelocity(0, -0.8);
	temp->addComponent<SpriteComponent>("assets/!Flame.png", true, 100);
	temp->getComponent<SpriteComponent>().Play("walkw");
	temp->addComponent<ColliderComponent>("bullet");
	temp->addGroup(groupBullet);
	Game::bullets.emplace_back(temp);
}