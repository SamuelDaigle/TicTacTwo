#pragma once

class IWindowAPI;

class LineRenderer
{
public:
	LineRenderer();
	~LineRenderer();

	void addLine(const Line& _line);
	void draw(IWindowAPI & _windowAPI) const;

private:
	bool isLineExists(const Line& _line);
	void drawHoritonzalLine(IWindowAPI & _windowAPI, const Line * _line) const;
	void drawVerticalLine(IWindowAPI & _windowAPI, const Line * _line) const;
	void drawUpDiagonalLine(IWindowAPI & _windowAPI, const Line * _line) const;
	void drawDownDiagonalLine(IWindowAPI & _windowAPI, const Line * _line) const;

private:
	const int TILE_SIZE = 70;
	const int TILE_HALF_SIZE = 35;
	vector<const Line*> lines;
};

