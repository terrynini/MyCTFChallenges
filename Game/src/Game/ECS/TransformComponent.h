#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include "../Game.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	int height = 48;
	int width = 48;
	int scale = 1;
	int speed = 3;
	TransformComponent() { position.x = position.y = 0; }
	TransformComponent(int sc) 
	{ 
		position.Zero();
		scale = sc; 
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	void init() override
	{
		velocity.Zero();
	}
	void setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }
	void update() override
	{
		float t;
		t = position.x + velocity.x * speed;
		if (t <= 0)
			t = 0;
		else if (t >= W_WIDTH - 47)
			t = W_WIDTH - 47;
		position.x = t;

		t = position.y + velocity.y * speed;
		if (t <= 0)
			t = 0;
		else if (t >= W_HEIGHT - 47)
		{
			t = W_HEIGHT - 47;
		}
		position.y = t;
	}
};