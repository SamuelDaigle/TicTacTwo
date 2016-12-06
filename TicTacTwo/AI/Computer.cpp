#include "stdafx.h"

Computer::Computer(const Grid & _grid, const Tile::TILE_TYPE &_playerTileType)
{
	grid = &_grid;
	computerTileType = _playerTileType;
}


Computer::~Computer()
{
}

Tile::TILE_TYPE Computer::getComputerTileType() const
{
	return computerTileType;
}

vector<Point> Computer::getAllEmptyTiles() const
{
	vector<Point> emptyTiles;
	for (unsigned int indexX = 0; indexX < 6; ++indexX)
	{
		for (unsigned int indexY = 0; indexY < 6; ++indexY)
		{
			Tile * tile = grid->getTile(indexX, indexY);
			if (tile != nullptr && tile->getTileType() == Tile::EMPTY_TYPE)
			{
				emptyTiles.push_back(grid->getTile(indexX, indexY)->getPosition());
			}
		}
	}
	return emptyTiles;
}

const Point * Computer::getRandomTile() const
{
	vector<Point> availablePoint = getAllEmptyTiles();

	if (availablePoint.empty())
	{
		throw std::runtime_error("No tiles available");
	}

	unsigned int randomTile = rand() % availablePoint.size();
	Point * tile = new Point(availablePoint.at(randomTile));
	return tile;
}
