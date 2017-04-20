/*
 * Rectangle.h
 *
 *      Author: Aidan
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <memory>

class Rectangle
{
public:
	Rectangle(float topLeftX, float topLeftY, float width, float height);
	~Rectangle();
	std::shared_ptr<Rectangle> Intersects(const Rectangle& rect) const;
	bool operator==(const Rectangle& rect) const;

	float MinX() const;
	float MaxX() const;
	float MinY() const;
	float MaxY() const;
	float W() const;
	float H() const;

private:
	Rectangle();
	float minX;
	float maxX;
	float minY;
	float maxY;
};



#endif /* RECTANGLE_H_ */
