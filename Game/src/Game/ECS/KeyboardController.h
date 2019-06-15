#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	int bullet;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		bullet = 0;
	}
	void update() override
	{
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("idlew");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("idlea");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("idled");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("idles");
				break;
			default:
				break;
			}
		}
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W]) { transform->velocity.y = -1; sprite->Play("walkw"); }
		if (state[SDL_SCANCODE_S]) { transform->velocity.y = 1; sprite->Play("walks"); }
		if (state[SDL_SCANCODE_A]) { transform->velocity.x = -1; sprite->Play("walka"); }
		if (state[SDL_SCANCODE_D]) { transform->velocity.x = 1; sprite->Play("walkd"); }
		if (state[SDL_SCANCODE_SPACE]) {
			if (bullet == 0) 
			{
				Game::addBullet(transform->position.x, transform->position.y);
				bullet = 20;
			}
		}
		if ( bullet != 0)
			bullet--;
	}
};