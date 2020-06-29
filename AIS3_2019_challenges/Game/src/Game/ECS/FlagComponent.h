#pragma once
#include "ECS.h"

class FlagComponent : public Component
{
public:
	FlagComponent(int x, int y, bool b)
	{
		xpos = x;
		ypos = y;
		bright = b;
	}
	void Draw() 
	{
		Game::DelTile(xpos, ypos);
		Game::AddTile((int)bright, xpos, ypos);
	}
	int xpos;
	int ypos;
	bool bright;
};