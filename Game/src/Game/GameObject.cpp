#include "GameObject.h"
#include "TextureLoader.h"

GameObject::GameObject(const char* texturesheet, int x, int y) 
{
	objTexture = TextureLoader::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
	srcRect.h = 48;
	srcRect.w = 48;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.h = 48*2;
	destRect.w = 48*2;
	destRect.x = xpos;
	destRect.y = ypos;
}
GameObject::~GameObject()
{
}
void GameObject::update()
{
	xpos++;
	ypos++;
	destRect.x = xpos;
	destRect.y = ypos;
}
void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}