#pragma once
#include "stdafx.h"

class GameConfiguration
{
public:
	enum DIFFICULTY
	{
		EASY,
		NORMAL
	};

	GameConfiguration();
	~GameConfiguration();

	char * playerImage;
	char * computerImage;
	char * emptyTileImage;
	bool loadLastGame;
	Tile::TILE_TYPE playerType;
	Tile::TILE_TYPE computerType;
	DIFFICULTY gameDifficulty;
	
};