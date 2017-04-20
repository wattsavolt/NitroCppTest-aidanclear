/*
 * main.cpp

 *
 *  Created on: 2 Apr 2017
 *      Author: Aidan
 */

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <functional>
#include "RectangleIntersectionUtil.h"

using namespace std;


//ReadRectanglesFromJSON tests

//Check two rectangles get loaded from file.
bool Test1()
{
	const Rectangle expected1(20, 20, 5, 5);
	const Rectangle expected2(40, 10, 2, 7);
	vector<shared_ptr<Rectangle>> rectangles;
	RectangleIntersectionUtil::ReadRectanglesFromJSON("test1.json", rectangles);
	if(rectangles.size() != 2)
	{
		return false;
	}
	return expected1 == *rectangles[0] && expected2 == *rectangles[1];
}

//Check rectangle with floating point values gets loaded correctly.
bool Test2()
{
	const Rectangle expected(20.1f, 20.3f, 5.9f, 6.0f);
	vector<shared_ptr<Rectangle>> rectangles;
	RectangleIntersectionUtil::ReadRectanglesFromJSON("test2.JSON", rectangles);
	if(rectangles.size() != 1)
	{
		return false;
	}
	return expected == *rectangles[0];
}

//Check rectangle with negative X and Y gets loaded correctly.
bool Test3()
{
	const Rectangle expected(-20.1f, -20.3f, 5.9f, 6.0f);
	vector<shared_ptr<Rectangle>> rectangles;
	RectangleIntersectionUtil::ReadRectanglesFromJSON("test3.JSON", rectangles);
	if(rectangles.size() != 1)
	{
		return false;
	}
	return expected == *rectangles[0];
}

//Check max of 10 rectangles get loaded when there is more in the file.
bool Test4()
{
	vector<shared_ptr<Rectangle>> rectangles;
	try
	{
		RectangleIntersectionUtil::ReadRectanglesFromJSON("test4.JSON", rectangles);
	}
	catch(exception& e)
	{
		return false;
	}
	return rectangles.size() == 10;
}

//Check correct error is thrown for invalid JSON format in the file.
bool Test5()
{
	vector<shared_ptr<Rectangle>> rectangles;
	try
	{
		RectangleIntersectionUtil::ReadRectanglesFromJSON("test5.JSON", rectangles);
	}
	catch(exception& e)
	{
		return e.what() == RectangleIntersectionUtil::INVALID_JSON_ERROR;
	}
	return false;
}

//Check correct error is thrown when rectangle has incorrect element count.
bool Test6()
{
	vector<shared_ptr<Rectangle>> rectangles;
	try
	{
		RectangleIntersectionUtil::ReadRectanglesFromJSON("test6.JSON", rectangles);
	}
	catch(exception& e)
	{
		return e.what() == RectangleIntersectionUtil::INCORRECT_ELEMENT_COUNT_ERROR;
	}
	return false;
}

//Check correct error is thrown when rectangle does not have 4 elements.
bool Test7()
{
	vector<shared_ptr<Rectangle>> rectangles;
	try
	{
		RectangleIntersectionUtil::ReadRectanglesFromJSON("test7.JSON", rectangles);
	}
	catch(exception& e)
	{
		return e.what() == RectangleIntersectionUtil::INCORRECT_RECTANGLE_SIZE_ERROR;
	}
	return false;
}

//Intersects tests

//Check two non-intersecting rectangles are not reported otherwise.
bool Test8()
{
	const Rectangle a(30, 10, 10, 10);
	const Rectangle b(19.99f, 10, 10, 10);
	return a.Intersects(b) == nullptr;
}

//Check intersection not reported for two non-intersecting side touching rectangles.
bool Test9()
{
	const Rectangle a(30, 10, 10, 10);
	const Rectangle b(20, 10, 10, 10);
	return a.Intersects(b) == nullptr;
}

//Check intersection rectangle of two rectangles is calculated correctly.
bool Test10()
{
	const Rectangle a(30, 10, 10, 10);
	const Rectangle b(20.1f, 10, 10, 10);
	const Rectangle expected(30, 10, 0.1f, 10);
	std::shared_ptr<Rectangle> actual = a.Intersects(b);
	return actual != nullptr && expected == *actual;
}

//Check intersection rectangle of two rectangles with negative X and Y values is calculated correctly.
bool Test11()
{
	const Rectangle a(-10, -10, 10, 10);
	const Rectangle b(-19.9f, -10, 10, 10);
	const Rectangle expected(-10, -10, 0.1f, 10);
	std::shared_ptr<Rectangle> actual = a.Intersects(b);
	return actual != nullptr && expected == *actual;
}

//Check intersection of two of the same rectangles is reported correctly
bool Test12()
{
	const Rectangle a(-10, -10, 10, 10);
	std::shared_ptr<Rectangle> intersection = a.Intersects(a);
	return intersection != nullptr && a == *intersection;
}

//Check intersection two rectangles where one is contained in the other is calculated correctly.
bool Test13()
{
	const Rectangle a(30, 10, 10, 10);
	//B is contained in a.
	const Rectangle b(32, 4, 4, 4);
	std::shared_ptr<Rectangle> intersection = a.Intersects(b);
	return intersection != nullptr && b == *intersection;
}

///FindIntersectingRectangles tests

//Check that correct intersection is returned for two intersecting rectangles.
bool Test14()
{
	vector<shared_ptr<Rectangle>> rectangles;
	rectangles.push_back(make_shared<Rectangle>(-10, -26.1, 10, 10));
	rectangles.push_back(make_shared<Rectangle>(-10, -19.9f, 10, 10));
	const Rectangle expected(-10, -26.1, 10, 3.8f);
	vector<shared_ptr<RectangleIntersection>> intersections;
	RectangleIntersectionUtil::FindIntersectingRectangles(rectangles, intersections);
	if(intersections.size() != 1)
	{
		return false;
	}
	const Rectangle& actual = *(intersections[0]->GetRectangle());
	return expected == actual;
}

//Check that no intersection is returned for two non-intersecting rectangles.
bool Test15()
{
	vector<shared_ptr<Rectangle>> rectangles;
	rectangles.push_back(make_shared<Rectangle>(-10, -26.1, 10, 10));
	rectangles.push_back(make_shared<Rectangle>(10, 19.9f, 10, 10));
	vector<shared_ptr<RectangleIntersection>> intersections;
	RectangleIntersectionUtil::FindIntersectingRectangles(rectangles, intersections);
	return intersections.size() == 0;
}

//Check that intersections for three intersecting rectangles are returned in order of rectangle index and number of rectangles in the intersection.
bool Test16()
{
	vector<shared_ptr<Rectangle>> rectangles;
	rectangles.push_back(make_shared<Rectangle>(50, 50, 20, 20));
	rectangles.push_back(make_shared<Rectangle>(60, 50, 20, 20));
	rectangles.push_back(make_shared<Rectangle>(50, 40, 20, 20));
	vector<shared_ptr<RectangleIntersection>> intersections;
	RectangleIntersectionUtil::FindIntersectingRectangles(rectangles, intersections);
	if(intersections.size() != 4)
	{
		return false;
	}
	//Check Intersection 1 (Rectangles 1 and 2)
	std::vector<uint32_t>& v = intersections[0]->GetIndices();
	shared_ptr<Rectangle> r = intersections[0]->GetRectangle();
	if(v[0] != 0 || v[1] != 1 || r->MinX() != 60 || r->MaxY() != 50 || r->W() != 10 || r->H() != 20)
	{
		return false;
	}
	//Check Intersection 2 (Rectangles 1 and 3)
	v = intersections[1]->GetIndices();
	r = intersections[1]->GetRectangle();
	if(v[0] != 0 || v[1] != 2 || r->MinX() != 50 || r->MaxY() != 40 || r->W() != 20 || r->H() != 10)
	{
		return false;
	}
	//Check Intersection 3 (Rectangles 2 and 3)
	v = intersections[2]->GetIndices();
	r = intersections[2]->GetRectangle();
	if(v[0] != 1 || v[1] != 2 || r->MinX() != 60 || r->MaxY() != 40 || r->W() != 10 || r->H() != 10)
	{
		return false;
	}
	//Check Intersection 4 (Rectangles 1, 2 and 3)
	v = intersections[3]->GetIndices();
	r = intersections[3]->GetRectangle();
	if(v[0] != 0 || v[1] != 1 || v[2] != 2 || r->MinX() != 60 || r->MaxY() != 40 || r->W() != 10 || r->H() != 10)
	{
		return false;
	}
	return true;
}

//Check function works with max number of intersections. The file will have 10 of the same rectangle.
bool Test17()
{
	vector<shared_ptr<Rectangle>> rectangles;
	RectangleIntersectionUtil::ReadRectanglesFromJSON("test17.json", rectangles);
	vector<shared_ptr<RectangleIntersection>> intersections;
	RectangleIntersectionUtil::FindIntersectingRectangles(rectangles, intersections);
	return intersections.size() == 1013;
}


//Add tests to be called.
static const function<bool()> tests[] =
{
	&Test1,
	&Test2,
	&Test3,
	&Test4,
	&Test5,
	&Test6,
	&Test7,
	&Test8,
	&Test9,
	&Test10,
	&Test11,
	&Test12,
	&Test13,
	&Test14,
	&Test15,
	&Test16,
	&Test17
};

int main()
{
	//Execute tests.
	uint32_t index = 1;
	for(auto test : tests)
	{
		if(test())
		{
			cout << "Test " << index << " passed." << endl;
		}
		else
		{
			cout << "Test " << index << " failed." << endl;
		}
		++index;
	}
	return 1;
}


