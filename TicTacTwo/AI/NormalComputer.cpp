#include "stdafx.h"


NormalComputer::NormalComputer(const Grid & _grid, const Tile::TILE_TYPE &_playerTileType) :
Computer(_grid, _playerTileType)
{
}


NormalComputer::~NormalComputer()
{
}

const Point * NormalComputer::getChoice() const
{
	vector<const Point*> scoringPoints = getComputerPotentialPoints();
	vector<const Point*> blockingPoints = getOpponentPotentialPoints();

	const Point * chosenPosition = nullptr;

	if (scoringPoints.empty() && blockingPoints.empty())
	{
		chosenPosition = getRandomTile();
	}
	else
	{
		int scoreValue = 0;
		int blockValue = 0;
		vector<const Point*> bestScoringChoices = getMostOccurentPoints(scoringPoints);
		vector<const Point*> bestBlockingChoices = getMostOccurentPoints(blockingPoints);
		vector<const Point*> commonPoints = getCommonPoints(bestBlockingChoices, bestScoringChoices);
		if (!bestBlockingChoices.empty())
		{
			blockValue = getDoublons(bestBlockingChoices.at(0), blockingPoints);
		}
		if (!bestScoringChoices.empty())
		{
			scoreValue = getDoublons(bestScoringChoices.at(0), scoringPoints);
		}

		if (!commonPoints.empty())
		{
			int randomNumber = rand() % commonPoints.size();
			chosenPosition = commonPoints.at(randomNumber);
		}
		else if (scoreValue > blockValue)
		{	
			int randomNumber = rand() % bestScoringChoices.size();
			chosenPosition = bestScoringChoices.at(randomNumber);
		}
		else if (scoreValue < blockValue)
		{
			int randomNumber = rand() % bestBlockingChoices.size();
			chosenPosition = bestBlockingChoices.at(randomNumber);
		}
		else
		{
			vector<const Point*> allBestChoices;
			allBestChoices.reserve(bestBlockingChoices.size() + bestScoringChoices.size());
			allBestChoices.insert(allBestChoices.end(), bestScoringChoices.begin(), bestScoringChoices.end());
			allBestChoices.insert(allBestChoices.end(), bestBlockingChoices.begin(), bestBlockingChoices.end());
			int randomNumber = rand() % allBestChoices.size();
			chosenPosition = allBestChoices.at(randomNumber);
		}
	}
	return chosenPosition;
}

vector<const Point*> NormalComputer::getOpponentPotentialPoints() const
{
	//Get opponent lines
	vector<Line*> allLines = grid->getLines();
	vector<const Line*> opponentLines;
	for (Line * line : allLines)
	{
		if (line->getFrontTile().getTileType() != computerTileType)
		{
			opponentLines.push_back(line);
		}
	}

	//Get valid positions before and after each lines
	vector<const Point*> points;
	for (const Line * line : opponentLines)
	{
		vector<const Point*> afterAndBeforeLinePoints = getAfterAndBeforeValidPoint(*line);
		for (const Point * point : afterAndBeforeLinePoints)
		{
			points.push_back(point);
		}
	}

	//Get valid positions between tiles
	vector<const Point*> otherPoints = getValidPositionsBetweenTiles((computerTileType == Tile::X_TYPE) ? Tile::O_TYPE : Tile::X_TYPE);
	points.reserve(points.size() + otherPoints.size());
	points.insert(points.end(), otherPoints.begin(), otherPoints.end());

	return points;
}

vector<const Point*> NormalComputer::getComputerPotentialPoints() const
{
	//Get computer line's
	vector<Line*> allLines = grid->getLines();
	vector<const Line*> computerLines;
	for (Line * line : allLines)
	{
		if (line->getFrontTile().getTileType() == computerTileType)
		{
			computerLines.push_back(line);
		}
	}

	//Get valid positions before and after each lines
	vector<const Point*> points;
	for (const Line * line : computerLines)
	{
		vector<const Point*> afterAndBeforeLinePoints = getAfterAndBeforeValidPoint(*line);
		for (const Point * point : afterAndBeforeLinePoints)
		{
			points.push_back(point);
		}
	}

	//Get valid positions between tiles
	vector<const Point*> otherPoints = getValidPositionsBetweenTiles(computerTileType);
	points.reserve(points.size() + otherPoints.size());
	points.insert(points.end(), otherPoints.begin(), otherPoints.end());
	return points;
}

vector<const Point*> NormalComputer::getAfterAndBeforeValidPoint(const Line & _line) const
{
	vector<const Point*> points;
	Point lineVariation = _line.getLineVariation();
	const Point * pointBeforeLine = _line.getPointBeforeLine();
	const Point * pointAfterLine = _line.getPointAfterLine();

	Tile * tileBeforeLine = grid->getTile(pointBeforeLine);
	Tile * tileAfterLine = grid->getTile(pointAfterLine);

	if (tileBeforeLine != nullptr && tileBeforeLine->getTileType() == Tile::EMPTY_TYPE)
	{
		points.push_back(pointBeforeLine);
	}
	if (tileAfterLine != nullptr && tileAfterLine->getTileType() == Tile::EMPTY_TYPE)
	{
		points.push_back(pointAfterLine);
	}
	return points;
}

int NormalComputer::getDoublons(const Point * _point, vector<const Point *> _points) const
{
	int numberOfOccurence = 0;
	for (const Point * point : _points)
	{
		if (*point == *_point)
		{
			numberOfOccurence++;
		}
	}
	return numberOfOccurence;
}

vector<const Point*> NormalComputer::getMostOccurentPoints(vector<const Point*> _points) const
{
	int biggestOccurence = 0;
	vector<const Point*> mostOccurentPoints;
	for (const Point * point : _points)
	{
		int pointOccurences = getDoublons(point, _points);
		if (pointOccurences > biggestOccurence)
		{
			biggestOccurence = pointOccurences;
			mostOccurentPoints.clear();
			mostOccurentPoints.push_back(point);
		}
		else if (pointOccurences == biggestOccurence)
		{
			mostOccurentPoints.push_back(point);
		}
	}

	return mostOccurentPoints;
}
vector<const Point*> NormalComputer::getCommonPoints(vector<const Point*> _points1, vector<const Point*> _points2) const
{
	vector<const Point*> commonPoints;
	for (const Point * point1 : _points1)
	{
		for (const Point * point2 : _points2)
		{
			if (*point1 == *point2)
			{
				commonPoints.push_back(point1);
			}
		}
	}
	return commonPoints;
}

vector<const Point*> NormalComputer::getValidPositionsBetweenTiles(Tile::TILE_TYPE _type) const
{
	vector<Point> allTiles = getAllEmptyTiles();
	vector<const Point*> tilesBetweenSameType;
	for (Point point : allTiles)
	{
		vector<Tile*> tilesToCheck;
		tilesToCheck.push_back(grid->getTile(point.x - 1, point.y)); //		left
		tilesToCheck.push_back(grid->getTile(point.x + 1, point.y)); //		right
		tilesToCheck.push_back(grid->getTile(point.x, point.y - 1)); //		top
		tilesToCheck.push_back(grid->getTile(point.x, point.y + 1)); //		bottom
		tilesToCheck.push_back(grid->getTile(point.x - 1, point.y - 1)); // top left
		tilesToCheck.push_back(grid->getTile(point.x + 1, point.y + 1)); // bottom right
		tilesToCheck.push_back(grid->getTile(point.x - 1, point.y + 1)); // bottom left
		tilesToCheck.push_back(grid->getTile(point.x + 1, point.y - 1)); // top right

		for (unsigned int index = 0; index < tilesToCheck.size(); index += 2)
		{
			if (tilesToCheck[index] != nullptr && tilesToCheck[index + 1] != nullptr)
			{
				if (tilesToCheck[index]->getTileType() == _type && tilesToCheck[index + 1]->getTileType() == _type)
				{
					tilesBetweenSameType.push_back(&grid->getTile(&point)->getPosition());
				}			
			}
		}
		
		tilesToCheck.clear();
	}
	return tilesBetweenSameType;
}