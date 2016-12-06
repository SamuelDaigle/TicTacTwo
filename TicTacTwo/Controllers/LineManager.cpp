#include "stdafx.h"

LineManager::LineManager(Grid & _grid)
{
	grid = &_grid;
}

LineManager::~LineManager()
{

}

vector<Line*> LineManager::updateLines(const Point & _point)
{
	vector<Line*> existingLines = grid->getLines();
	vector<Line*> createdLines;

	Tile * currentTile = grid->getTile(&_point);

	for (int xVariation = -1; xVariation <= 1; xVariation++)
	{
		for (int yVariation = -1; yVariation <= 1; yVariation++)
		{
			if (!(xVariation == 0 && yVariation == 0))
			{
				Tile * aroundTile = grid->getTile(_point.x + xVariation, _point.y + yVariation);
				if (aroundTile != nullptr && currentTile->getTileType() == aroundTile->getTileType())
				{
					if (!chosenTileContinuesExistingLines(currentTile, aroundTile, existingLines))
					{
						if (!chosenTileContinuesExistingLines(aroundTile, currentTile, createdLines))
						{
							Line * newLine = new Line();
							Tile * frontTile = nullptr;
							Tile * backTile = nullptr;

							if (currentTile->getPosition().x < aroundTile->getPosition().x)
							{
								frontTile = aroundTile;
								backTile = currentTile;
							}
							else if (currentTile->getPosition().x > aroundTile->getPosition().x)
							{
								frontTile = currentTile;
								backTile = aroundTile;
							}
							else if (currentTile->getPosition().y < aroundTile->getPosition().y)
							{
								frontTile = aroundTile;
								backTile = currentTile;
							}
							else if (currentTile->getPosition().y > aroundTile->getPosition().y)
							{
								frontTile = currentTile;
								backTile = aroundTile;
							}
							newLine->addFront(frontTile);
							newLine->addBack(backTile);

							if (getAdjacentLine(newLine, existingLines) == nullptr && !isLineOnExistingLine(newLine, existingLines))
							{
								createdLines.push_back(newLine);
							}
						}
					}
				}
			}
		}
	}
	for each (Line * line in createdLines)
	{
		grid->addLine(line);
		cout << endl << "New line | " << "Type : " << (char)line->getBackTile().getTileType();
		cout << " Size : " << line->getSize() << " Orientation : " << (char)line->getOrientation() << " |" << endl;
	}
	cout << endl << "Lines created : " << createdLines.size() << endl;

	return createdLines;
}

bool LineManager::chosenTileContinuesExistingLines(Tile * _currentTile, Tile * _aroundTile, vector<Line*> & _lines)
{
	bool aroundTileIsManaged = false;
	int numberOfLines = _lines.size();
	for (int index = 0; index < numberOfLines; index++)
	{
		Line * line = _lines[index];
		Tile firstTile = line->getFrontTile();
		Tile lastTile = line->getBackTile();
		const Point * positionAfterLine = line->getPointAfterLine();
		const Point * positionBeforeLine = line->getPointBeforeLine();

		if (firstTile.getPosition() == _aroundTile->getPosition() && *positionAfterLine == _currentTile->getPosition())
		{
			line->addFront(_currentTile);
			aroundTileIsManaged = true;

			Tile * tileAfterLine = grid->getTile(line->getPointAfterLine());
			if (tileAfterLine != nullptr && tileAfterLine->getTileType() == _currentTile->getTileType())
			{
				Line * adjacentLine = getAdjacentLine(line, _lines);
				if (adjacentLine != nullptr)
				{
					addFrontRecusive(line, grid->getTile(line->getPointAfterLine()));
					int adjacentLinePosition = getLinePosition(adjacentLine, _lines);
					_lines.erase(_lines.begin() + adjacentLinePosition);
					grid->eraseLine(adjacentLinePosition);
					numberOfLines--;
				}
				else
				{
					line->addFront(grid->getTile(line->getPointAfterLine()));
				}
			}
		}
		else if (lastTile.getPosition() == _aroundTile->getPosition()
			&& *positionBeforeLine == _currentTile->getPosition())
		{
			line->addBack(_currentTile);

			Tile * tileBeforeLine = grid->getTile(line->getPointBeforeLine());
			if (tileBeforeLine != nullptr && tileBeforeLine->getTileType() == _currentTile->getTileType())
			{
				line->addBack(grid->getTile(line->getPointBeforeLine()));
			}
			aroundTileIsManaged = true;
		}
	}
	return aroundTileIsManaged;
}

Line * LineManager::getAdjacentLine(Line * _line, vector<Line*> _lines)
{

	for (Line * line : _lines)
	{
		if (line->getOrientation() == _line->getOrientation() &&
			line->getFrontTile().getTileType() == _line->getFrontTile().getTileType() &&
			(*_line->getPointAfterLine() == line->getBackTile().getPosition() ||
			*_line->getPointBeforeLine() == line->getFrontTile().getPosition()))
		{
			return line;
		}
	}
	return nullptr;
}

int LineManager::getLinePosition(Line * _line, vector<Line*> _lines)
{
	for (int index = 0; index < _lines.size(); index++)
	{
		if (_line == _lines[index]) return index;
	}
	return -1;
}

bool LineManager::isLineOnExistingLine(Line * _checkedLine, vector<Line*> _lines)
{
	for (Line * comparedLine : _lines)
	{
		if (comparedLine->getOrientation() == _checkedLine->getOrientation() &&
			comparedLine->getFrontTile().getTileType() == _checkedLine->getFrontTile().getTileType())
		{
			Line::LINE_ORIENTATION orientation = comparedLine->getOrientation();
			
			switch (orientation)
			{
			case Line::HORIZONTAL:
				if (doHorizontalLinesCross(_checkedLine, comparedLine)) return true;
				break;

			case Line::VERTICAL:
				if (doVerticalLinesCross(_checkedLine, comparedLine)) return true;
				break;

			case Line::DOWN_DIAGONAL:
				if (doDownDiagonalLinesCross(_checkedLine, comparedLine)) return true;
				break;
				
			case Line::UP_DIAGONAL:
				if (doUpDiagonalLinesCross(_checkedLine, comparedLine)) return true;
				break;
			}
		}
	}
	return false;
}

bool LineManager::doHorizontalLinesCross(Line * _checkedLine, Line * _comparedLine)
{
	Point comparedLineFront = _comparedLine->getFrontTile().getPosition();
	Point checkedLineFront = _checkedLine->getFrontTile().getPosition();
	Point comparedLineBack = _comparedLine->getBackTile().getPosition();
	Point checkedLineBack = _checkedLine->getBackTile().getPosition();

	if (comparedLineFront.y == checkedLineFront.y &&
		((checkedLineFront.x >= comparedLineBack.x && checkedLineBack.x <= comparedLineFront.x)
		|| (checkedLineBack.x <= comparedLineFront.x && checkedLineFront.x >= comparedLineBack.x)))
	{
		return true;
	}

	return false;
}

bool LineManager::doVerticalLinesCross(Line * _checkedLine, Line * _comparedLine)
{
	Point comparedLineFront = _comparedLine->getFrontTile().getPosition();
	Point checkedLineFront = _checkedLine->getFrontTile().getPosition();
	Point comparedLineBack = _comparedLine->getBackTile().getPosition();
	Point checkedLineBack = _checkedLine->getBackTile().getPosition();

	if (comparedLineFront.x == checkedLineFront.x &&
		((checkedLineFront.y >= comparedLineBack.y && checkedLineBack.y <= comparedLineFront.y)
		|| (checkedLineBack.y <= comparedLineFront.y && checkedLineFront.y >= comparedLineBack.y)))
	{
		return true;
	}

	return false;
}

bool LineManager::doUpDiagonalLinesCross(Line * _checkedLine, Line * _comparedLine)
{
	Point comparedLineFront = _comparedLine->getFrontTile().getPosition();
	Point checkedLineFront = _checkedLine->getFrontTile().getPosition();
	Point comparedLineBack = _comparedLine->getBackTile().getPosition();
	Point checkedLineBack = _checkedLine->getBackTile().getPosition();

	if (checkedLineBack.x + checkedLineBack.y == comparedLineBack.x + comparedLineBack.y &&
		((checkedLineFront.x >= comparedLineBack.x && checkedLineBack.x <= comparedLineFront.x)
		|| (checkedLineBack.x <= comparedLineFront.x && checkedLineFront.x >= comparedLineBack.x)))
	{
		return true;
	}

	return false;
}

bool LineManager::doDownDiagonalLinesCross(Line * _checkedLine, Line * _comparedLine)
{
	Point comparedLineFront = _comparedLine->getFrontTile().getPosition();
	Point checkedLineFront = _checkedLine->getFrontTile().getPosition();
	Point comparedLineBack = _comparedLine->getBackTile().getPosition();
	Point checkedLineBack = _checkedLine->getBackTile().getPosition();

	if (checkedLineBack.x - checkedLineBack.y == comparedLineBack.x - comparedLineBack.y &&
		((checkedLineFront.x >= comparedLineBack.x && checkedLineBack.x <= comparedLineFront.x)
		|| (checkedLineBack.x <= comparedLineFront.x && checkedLineFront.x >= comparedLineBack.x)))
	{
		return true;
	}

	return false;
}

void LineManager::addFrontRecusive(Line * _line, Tile * _toAdd)
{
	_line->addFront(_toAdd);
	Tile * nextTile = grid->getTile(_line->getPointAfterLine());
	if (nextTile != nullptr && nextTile->getTileType() == _toAdd->getTileType())
	{
		addFrontRecusive(_line, nextTile);
	}
}