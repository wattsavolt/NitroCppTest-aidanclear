/*
 * RectangleIntersection.h
 *
 *      Author: Aidan
 */

#ifndef RECTANGLEINTERSECTION_H_
#define RECTANGLEINTERSECTION_H_

#include <memory>
#include <vector>
#include "Rectangle.h"

class RectangleIntersection
{
public:
	RectangleIntersection(std::shared_ptr<Rectangle> rectangle, std::vector<uint32_t> indices);
	~RectangleIntersection();

	std::shared_ptr<Rectangle> GetRectangle() const;
	std::vector<uint32_t>& GetIndices();

private:
	//Intersection rectangle
	std::shared_ptr<Rectangle> rectangle;
	std::vector<uint32_t> indices;
};


#endif /* RECTANGLEINTERSECTION_H_ */
