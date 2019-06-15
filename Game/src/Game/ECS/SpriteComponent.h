#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureLoader.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frames = 0;
	int speed = 100;
	int offset = 0;
public:
	int animIndex = 1;
	std::map<const char*, Animation> animations;
	
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	SpriteComponent(const char* path, bool isAnimated, int frame)
	{
		animated = isAnimated;
		Animation idles = Animation(0, 1, 1, frame);
		Animation idlea = Animation(1, 1, 1, frame);
		Animation idled = Animation(2, 1, 1, frame);
		Animation idlew = Animation(3, 1, 1, frame);
		Animation walks = Animation(0, 0, 3, frame);
		Animation walka = Animation(1, 0, 3, frame);
		Animation walkd = Animation(2, 0, 3, frame);
		Animation walkw = Animation(3, 0, 3, frame);
		animations.emplace("idles", idles);
		animations.emplace("idlea", idlea);
		animations.emplace("idled", idled);
		animations.emplace("idlew", idlew);
		animations.emplace("walks", walks);
		animations.emplace("walka", walka);
		animations.emplace("walkd", walkd);
		animations.emplace("walkw", walkw);
		Play("idles");
		setTex(path);
	}
	~SpriteComponent()
	{
		//SDL_DestroyTexture(texture);
	}
	void setTex(const char* path)
	{
		texture = TextureLoader::LoadTexture(path);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}
	void SetSrc(int x, int y, int w, int h) 
	{
		srcRect.x = x;
		srcRect.y = y;
		srcRect.w = w;
		srcRect.h = h;
	}
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * (static_cast<int>((SDL_GetTicks() / speed) % frames) + offset);
			srcRect.y = animIndex * transform->height;
		}
		
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void render() override
	{
		TextureLoader::Draw(texture, srcRect, destRect);
	}
	void Play(const char* animName)
	{
		offset = animations[animName].offset;
		frames = animations[animName].frames;
		speed = animations[animName].speed;
		animIndex = animations[animName].index;
	}
};