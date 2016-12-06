#include "stdafx.h"

GameConfiguration::GameConfiguration()
{
	playerImage = "XType.bmp";
	computerImage = "OType.bmp";
	emptyTileImage = "emptySquare1.bmp";
	computerType = Tile::O_TYPE;
	playerType = Tile::X_TYPE;
	gameDifficulty = EASY;
}

GameConfiguration::~GameConfiguration(){}