#include "stdafx.h"
#include "IWindowAPI.h"


LineRenderer::LineRenderer()
{
}

LineRenderer::~LineRenderer()
{
	lines.clear();
}

void LineRenderer::addLine(const Line& _line)
{
	lines.push_back(&_line);
}

void LineRenderer::draw(IWindowAPI & _windowAPI) const
{
	const int TILE_SIZE = 70;
	for each (const Line* line in lines)
	{
		if (line->getSize() >= 3)
		{
			switch (line->getOrientation())
			{
			case Line::HORIZONTAL:
				drawHoritonzalLine(_windowAPI, line);
				break;
			case Line::VERTICAL:
				drawVerticalLine(_windowAPI, line);
				break;
			case Line::DOWN_DIAGONAL:
				drawDownDiagonalLine(_windowAPI, line);
				break;
			case Line::UP_DIAGONAL:
				drawUpDiagonalLine(_windowAPI, line);
				break;
			default:
				break;
			}
		}
	}
}

void LineRenderer::drawHoritonzalLine(IWindowAPI & _windowAPI, const Line * _line) const
{
	_windowAPI.drawLine((_line->getFrontTile().getPosition().x * TILE_SIZE) + TILE_SIZE,
		(_line->getFrontTile().getPosition().y) * TILE_SIZE + TILE_SIZE / 2,
		_line->getBackTile().getPosition().x * TILE_SIZE,
		_line->getBackTile().getPosition().y * TILE_SIZE + TILE_SIZE / 2,
		(_line->getFrontTile().getTileType() == Tile::O_TYPE) ? 0xFF0000 : 0x0000FF);
}

void LineRenderer::drawVerticalLine(IWindowAPI & _windowAPI, const Line * _line) const
{
	_windowAPI.drawLine((_line->getFrontTile().getPosition().x * TILE_SIZE) + TILE_HALF_SIZE,
		(_line->getFrontTile().getPosition().y) * TILE_SIZE + TILE_SIZE,
		_line->getBackTile().getPosition().x * TILE_SIZE + TILE_HALF_SIZE,
		_line->getBackTile().getPosition().y * TILE_SIZE,
		(_line->getFrontTile().getTileType() == Tile::O_TYPE) ? 0xFF0000 : 0x0000FF);
}

void LineRenderer::drawUpDiagonalLine(IWindowAPI & _windowAPI, const Line * _line) const
{
	_windowAPI.drawLine((_line->getFrontTile().getPosition().x * TILE_SIZE) + TILE_SIZE,
		(_line->getFrontTile().getPosition().y) * TILE_SIZE,
		_line->getBackTile().getPosition().x * TILE_SIZE,
		_line->getBackTile().getPosition().y * TILE_SIZE + TILE_SIZE,
		(_line->getFrontTile().getTileType() == Tile::O_TYPE) ? 0xFF0000 : 0x0000FF);
}

void LineRenderer::drawDownDiagonalLine(IWindowAPI & _windowAPI, const Line * _line) const
{
	_windowAPI.drawLine((_line->getFrontTile().getPosition().x * TILE_SIZE) + TILE_SIZE,
		(_line->getFrontTile().getPosition().y) * TILE_SIZE + TILE_SIZE,
		_line->getBackTile().getPosition().x * TILE_SIZE,
		_line->getBackTile().getPosition().y * TILE_SIZE,
		(_line->getFrontTile().getTileType() == Tile::O_TYPE) ? 0xFF0000 : 0x0000FF);
}