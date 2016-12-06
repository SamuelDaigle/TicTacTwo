#pragma once
#include "stdafx.h"

class NormalComputer : public Computer
{
public:
	NormalComputer(const Grid & _grid, const Tile::TILE_TYPE &_computerTileType);
	~NormalComputer();
	const Point * getChoice() const;
private:
	int getDoublons(const Point * _point, vector<const Point *> _points) const;
	vector<const Point*> getOpponentPotentialPoints() const;
	vector<const Point*> getComputerPotentialPoints() const;
	vector<const Point*> getAfterAndBeforeValidPoint(const Line & _line) const;
	vector<const Point*> getMostOccurentPoints(vector<const Point*> _points) const;
	vector<const Point*> getValidPositionsBetweenTiles(Tile::TILE_TYPE _type) const;
	vector<const Point*> getCommonPoints(vector<const Point*> _points1, vector<const Point*> _points2) const;
};
