#include "stdafx.h"

Point::Point( double _x, double _y )
{	
	x = _x;
	y = _y;
}

bool Point::operator == (const Point & point) const
{
	return (this->x == point.x && this->y == point.y);
}

bool Point::operator != (const Point & point) const
{
	return (this->x != point.x || this->y != point.y);
}