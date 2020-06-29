#pragma once

struct Animation
{
	int index;
	int offset;
	int frames;
	int speed;
	Animation() {}
	Animation(int i, int o, int f, int s)
	{
		index = i;
		offset = o;
		frames = f;
		speed = s;
	}
};