/*
 * RectangleIntersectionUtil.cpp

 *
 *  Created on: 5 Apr 2017
 *      Author: Aidan
 */

#include "RectangleIntersectionUtil.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <rapidjson/istreamwrapper.h>


//Errors for ReadRectanglesFromJSON
const std::string RectangleIntersectionUtil::FILE_NOT_FOUND_ERROR = "JSON file not found.";
const std::string RectangleIntersectionUtil::INVALID_JSON_ERROR = "Failed to parse JSON file. Invalid JSON format.";
const std::string RectangleIntersectionUtil::INCORECT_MEMBER_COUNT_ERROR = "Incorrect number of members in the input file.";
const std::string RectangleIntersectionUtil::NO_RECTANGLES_ERROR = "No rectangles found in the JSON file.";
const std::string RectangleIntersectionUtil::INCORRECT_ELEMENT_COUNT_ERROR = "A rectangle must have exactly 4 elements.";
const std::string RectangleIntersectionUtil::INCORRECT_RECTANGLE_SIZE_ERROR = "A rectangle's width and height must be greater than 0.";

void RectangleIntersectionUtil::ReadRectanglesFromJSON(std::string fileName, std::vector<std::shared_ptr<Rectangle>>& rectangles, unsigned int maxInputSize)
{
	// Parse the JSON file into DOM.
	std::ifstream ifs(fileName.c_str());
	if(!ifs)
	{
		throw std::invalid_argument(FILE_NOT_FOUND_ERROR);
	}
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document document;
	rapidjson::ParseResult validFormat = document.ParseStream(isw);
	if(!validFormat)
	{
		throw std::invalid_argument(INVALID_JSON_ERROR);
	}

	if(document.MemberCount() != 1)
	{
		throw std::invalid_argument(INCORECT_MEMBER_COUNT_ERROR);
	}

	if(!document["rects"].IsArray() || document["rects"].Size() < 1)
	{
		throw std::invalid_argument(NO_RECTANGLES_ERROR);
	}

	uint32_t numRects = std::min(document["rects"].Size(), maxInputSize);
	//Iterate through the rects array and create the rectangles from the input data.
	for (rapidjson::SizeType i = 0; i < numRects; ++i)
	{
		rapidjson::Value& docRect = document["rects"][i];
		if(docRect.MemberCount() != 4)
		{
			throw std::invalid_argument(INCORRECT_ELEMENT_COUNT_ERROR);
		}
		if(docRect["w"].GetFloat() <= 0.0f || docRect["h"].GetFloat() <= 0.0f)
		{
			throw std::invalid_argument(INCORRECT_RECTANGLE_SIZE_ERROR);
		}
		auto rectangle = std::make_shared<Rectangle>(docRect["x"].GetFloat(), docRect["y"].GetFloat(), docRect["w"].GetFloat(), docRect["h"].GetFloat());
		rectangles.push_back(rectangle);
	}
}

void RectangleIntersectionUtil::FindIntersectingRectangles(std::vector<std::shared_ptr<Rectangle>>& rectangles, std::vector<std::shared_ptr<RectangleIntersection>>& intersections)
{
	//Get intersections of all rectangles. This is an approach that would be slow with very large numbers of rectangles.
	for(uint32_t i = 0; i < rectangles.size(); ++i)
	{
		//Current number of intersections before modification.
		uint32_t numIntersections = intersections.size();
		//Check if the rectangle intersects with any existing rectangle intersections.
		for(uint32_t j = 0; j < numIntersections; ++j)
		{
			//indices to rectangles of this intersection
			std::vector<uint32_t>& indices = intersections[j]->GetIndices();
			//If the index of this rectangle is not greater than the indices in this intersection, do not check for an intersection.
			//If the same, this rectangle is already part of the intersection. If greater than, then the same intersection test
			//will be done later with another rectangle and this keeps the indices vector in order.
			bool skipCheck = false;
			for(uint32_t index : indices)
			{
				if(index >= i)
				{
					skipCheck = true;
					break;
				}
			}
			if(skipCheck)
			{
				continue;
			}
			std::shared_ptr<Rectangle> intersection = rectangles[i]->Intersects(*intersections[j]->GetRectangle());
			if(intersection)
			{
				//Copy indices of the intersection tested against and add the index of the current rectangle for the new intersection.
				std::vector<uint32_t> newIndices(indices);
				newIndices.push_back(i);
				//Create and add new rectangle intersection.
				intersections.push_back(std::make_shared<RectangleIntersection>(intersection, newIndices));
			}
		}
		//Check for intersections between current rectangle and rectangles that haven't been visited yet.
		for(uint32_t j = i + 1; j < rectangles.size(); ++j)
		{
			std::shared_ptr<Rectangle> intersection = rectangles[i]->Intersects(*rectangles[j]);
			if(intersection)
			{
				const uint32_t array[] = {i, j};
				std::vector<uint32_t> newIndices (array, array + sizeof(array) / sizeof(array[0]) );
				//Create and add new rectangle intersection.
				intersections.push_back(std::make_shared<RectangleIntersection>(intersection, newIndices));
			}
		}
	}
	//Sort the vector of intersections in ascending order by the rectangle indices and number of indices.
	std::sort(intersections.begin(), intersections.end(), SortVector);

}

bool RectangleIntersectionUtil::SortVector(std::shared_ptr<RectangleIntersection> a, std::shared_ptr<RectangleIntersection> b)
{
	std::vector<uint32_t>& indicesA = a->GetIndices();
	std::vector<uint32_t>& indicesB = b->GetIndices();
	if(indicesA.size() != indicesB.size())
	{
		return indicesA.size() < indicesB.size();
	}
	for(uint32_t i = 0; i < indicesA.size(); ++i)
	{
		if(indicesA[i] == indicesB[i])
		{
			continue;
		}
		return indicesA[i] < indicesB[i];
	}
	return false;
}






