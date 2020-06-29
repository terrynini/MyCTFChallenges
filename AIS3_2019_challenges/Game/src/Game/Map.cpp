#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map()
{

}
Map::~Map()
{

}

void Map::LoadMap( int sizeX, int sizeY)
{

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			Game::AddTile(0, x * 48, y * 48);
		}
	}
}