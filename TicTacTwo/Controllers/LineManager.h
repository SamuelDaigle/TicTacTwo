#pragma once
#include "stdafx.h"

class LineManager
{
	public:
		LineManager(Grid & _grid);
		~LineManager();

		vector<Line*> updateLines(const Point & _point);
		
	private:
		Line * getAdjacentLine(Line * _line, vector<Line*> _lines);
		bool chosenTileContinuesExistingLines(Tile * _currentTile, Tile * _aroundTile, vector<Line*> & _lines);
		bool isLineOnExistingLine(Line * _checkedLine, vector<Line*> _lines);
		int getLinePosition(Line * _line, vector<Line*> _lines);
		void addFrontRecusive(Line * _line, Tile * _toAdd);
		bool doHorizontalLinesCross(Line * _checkedLine, Line * _comparedLine);
		bool doVerticalLinesCross(Line * _checkedLine, Line * _comparedLine);
		bool doUpDiagonalLinesCross(Line * _checkedLine, Line * _comparedLine);
		bool doDownDiagonalLinesCross(Line * _checkedLine, Line * _comparedLine);

		Grid * grid;
};