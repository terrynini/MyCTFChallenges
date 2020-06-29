#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "ECS/ECS.h"
#include "TextureLoader.h"

class ColliderComponent;
constexpr auto FLAG_DELAY = 10;
constexpr auto FLAG_MAX = 40;
constexpr auto W_WIDTH = 720;
constexpr auto W_HEIGHT = 720;
class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
	static void AddTile(int id, int x, int y);
	static void DelTile(float x, float y);
	static SDL_Renderer* renderer;
	static 	SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	static std::vector<Entity*> flags;
	static std::vector<Entity*> bullets;
	static void addBullet(float x, float y);
	int point;
private:
	bool isRunning;
	int flagDelay;
	int stage;
	SDL_Window* window;
};
#endif
