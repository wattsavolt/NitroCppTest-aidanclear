/*
 * RectangleIntersectionUtil.h
 *
 *      Author: Aidan
 */

#ifndef RECTANGLEINTERSECTIONUTIL_H_
#define RECTANGLEINTERSECTIONUTIL_H_

#include <vector>
#include <memory>
#include <string>
#include "Rectangle.h"
#include "RectangleIntersection.h"

class RectangleIntersectionUtil
{
public:
	static void ReadRectanglesFromJSON(std::string fileName, std::vector<std::shared_ptr<Rectangle>>& rectangles, unsigned int maxInputSize = 10);
	static void FindIntersectingRectangles(std::vector<std::shared_ptr<Rectangle>>& rectangles, std::vector<std::shared_ptr<RectangleIntersection>>& intersections);

	//Errors for ReadRectanglesFromJSON
	static const std::string FILE_NOT_FOUND_ERROR;
	static const std::string INVALID_JSON_ERROR;
	static const std::string INCORECT_MEMBER_COUNT_ERROR;
	static const std::string NO_RECTANGLES_ERROR;
	static const std::string INCORRECT_ELEMENT_COUNT_ERROR;
	static const std::string INCORRECT_RECTANGLE_SIZE_ERROR;
private:
	static bool SortVector(std::shared_ptr<RectangleIntersection> a, std::shared_ptr<RectangleIntersection> b);
};



#endif /* RECTANGLEINTERSECTIONUTIL_H_ */
