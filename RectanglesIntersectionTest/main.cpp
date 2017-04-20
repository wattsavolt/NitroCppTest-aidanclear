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
#include "RectangleIntersectionUtil.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Incorrect number of arguments." << endl;
		return 0;
	}

	vector<shared_ptr<Rectangle>> rectangles;
	try
	{
		RectangleIntersectionUtil::ReadRectanglesFromJSON(argv[1], rectangles, 10);
	}
	catch(exception& e)
	{
		cerr << "Exception occurred reading JSON file." << endl;
		cerr << e.what() << endl;
		return 0;
	}

	vector<shared_ptr<RectangleIntersection>> intersections;
	RectangleIntersectionUtil::FindIntersectingRectangles(rectangles, intersections);

	//Display input data.
	cout << "Input:" << endl;
	uint32_t index = 1;
	for(shared_ptr<Rectangle> r : rectangles)
	{
		stringstream ss;
		ss << index << ": Rectangle at (" << r->MinX() << ", " << r->MaxY() << "), w = " << r->W() << ", h = " << r->H() << ".";
		cout << setw(7) << " " << ss.str() << endl;
		index++;
	}

	//Display results.
	cout << endl << "Intersections" << endl;
	for(shared_ptr<RectangleIntersection> intersection : intersections)
	{
		shared_ptr<Rectangle> r = intersection->GetRectangle();
		std::vector<uint32_t>& indices = intersection->GetIndices();
		stringstream ss;
		ss << "Between rectangle " << indices[0] + 1;
		for(uint32_t i = 1; i < indices.size() - 1; ++i)
		{
			ss << ", " << indices[i] + 1;
		}
		ss << " and " << indices[indices.size() - 1] + 1 << " at (" << r->MinX() << ", " << r->MaxY() << "), w = " << r->W() << ", h = " << r->H() << ".";
		cout << setw(7) << " " << ss.str() << endl;
	}
	return 1;
}


