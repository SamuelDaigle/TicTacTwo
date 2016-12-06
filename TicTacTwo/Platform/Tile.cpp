#include "stdafx.h"


Tile::Tile()
{
	type = TILE_TYPE::EMPTY_TYPE;
}

Tile::Tile(TILE_TYPE _type)
{
	type = _type;
}

Tile::~Tile()
{
}

Tile::TILE_TYPE Tile::getTileType() const
{
	return type;
}

void Tile::changeType(const TILE_TYPE &_type)
{
	if (type != EMPTY_TYPE)
	{
		throw std::runtime_error("Tile has already a type other then Empty.");
	}
	type = _type;
}

bool Tile::operator==(Tile &_tile)
{
	return (type == _tile.type);
}

void Tile::setPosition(const Point &_position)
{
	position = &_position;
}

const Point & Tile::getPosition() const
{
	return *position;
}

bool Tile::operator!=(Tile &_tile)
{
	return !(*this == _tile);
}