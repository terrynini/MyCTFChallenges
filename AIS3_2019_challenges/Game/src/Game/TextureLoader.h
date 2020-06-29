#pragma once
#include "Game.h"
#include <map>

class TextureLoader{
public:
	static SDL_Texture* LoadTexture(const char* path);
	static void Draw(SDL_Texture*, SDL_Rect, SDL_Rect);
	static std::map<const char*, SDL_Texture*> textures;
};