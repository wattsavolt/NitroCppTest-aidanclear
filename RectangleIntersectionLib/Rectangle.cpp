/*
 * Rectangle.cpp
 *
 *      Author: Aidan
 */
#include "Rectangle.h"
#include <math.h>

Rectangle::Rectangle(float topLeftX, float topLeftY, float width, float height)
{
	minX = topLeftX;
	maxX = topLeftX + width;
	minY = topLeftY - height;
	maxY = topLeftY;
}

Rectangle::Rectangle() : minX(0), maxX(0), minY(0), maxY(0) {}

Rectangle::~Rectangle() {}

std::shared_ptr<Rectangle> Rectangle::Intersects(const Rectangle& rect) const
{
	std::shared_ptr<Rectangle> intersection(new Rectangle());
	//Calculate intersection.
	intersection->maxX = fmin(maxX, rect.maxX);
	intersection->maxY = fmin(maxY, rect.maxY);
	intersection->minX = fmax(minX, rect.minX);
	intersection->minY = fmax(minY, rect.minY);
	//Determine if the rectangles intersect by checking if the intersection calculated is a proper rectangle.
	if(intersection->minX < intersection->maxX && intersection->minY < intersection->maxY)
	{
		return intersection;
	}
	return NULL;
}

bool Rectangle::operator==(const Rectangle& rect) const
{
	return maxX == rect.maxX && minX == rect.minX && maxY == rect.maxY && minY == rect.minY;
}

float Rectangle::MinX() const
{
	return minX;
}

float Rectangle::MaxX() const
{
	return maxX;
}

float Rectangle::MinY() const
{
	return minY;
}

float Rectangle::MaxY() const
{
	return maxY;
}

float Rectangle::W() const
{
	return maxX - minX;
}

float Rectangle::H() const
{
	return maxY - minY;
}

