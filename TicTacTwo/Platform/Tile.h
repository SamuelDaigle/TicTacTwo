#pragma once
#include "../Utility/point.h"

#include "stdafx.h"

class Tile
{
public:
	enum TILE_TYPE
	{
		X_TYPE = 'X',
		O_TYPE = 'O',
		EMPTY_TYPE = 'E'
	};
	Tile();
	Tile(TILE_TYPE _type);
	~Tile();
	TILE_TYPE getTileType() const;
	void changeType(const TILE_TYPE &_type);
	void setPosition(const Point &_position);
	const Point & getPosition() const;
	bool operator==(Tile &_tile);
	bool operator!=(Tile &_tile);
private:
	TILE_TYPE type;
	const Point * position;
};

