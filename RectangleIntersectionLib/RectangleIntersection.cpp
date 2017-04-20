/*
 * RectangleIntersection.cpp

 *      Author: Aidan
 */

#include "RectangleIntersection.h"

RectangleIntersection::RectangleIntersection(std::shared_ptr<Rectangle> rectangle, std::vector<uint32_t> indices)
: rectangle(rectangle), indices(std::move(indices)) {}

RectangleIntersection::~RectangleIntersection() {}

std::shared_ptr<Rectangle> RectangleIntersection::GetRectangle() const
{
	return rectangle;
}

std::vector<uint32_t>& RectangleIntersection::GetIndices()
{
	return indices;
}


