#pragma once

#include <vector>
#include <optional>

#include "point.h"


namespace chal {

        inline auto do_the_challenge_thing(const std::vector<Point>& input_polygon)
                -> std::vector<Point>
        {
            using PointIndex = long unsigned int;
            auto pointsOrder = [&](const PointIndex a, const PointIndex b) -> bool
            {
                //sweeping from left to right, with consistent settle if neeeded
                return input_polygon.at(a).x < input_polygon.at(b).x
                        || (input_polygon.at(a).x == input_polygon.at(b).x && input_polygon.at(a).y < input_polygon.at(b).y);
            };

            //Create a sweeping ordering of the points
            std::vector<PointIndex> sweeping(input_polygon.size());
            std::iota(sweeping.begin(), sweeping.end(), 0);
            std::sort(sweeping.begin(), sweeping.end(), pointsOrder);

            auto nextForwardPoint = [&](const PointIndex from, const bool upper) -> std::optional<PointIndex>
            {
                //Points of the polygon are indexed in order (counterclockwise)
                PointIndex a = (from+1)%sweeping.size();
                PointIndex b = from==0 ? sweeping.size()-1 : from-1;
                //We want to return the forward upper or lower neighbour.
                if(pointsOrder(a,from) && pointsOrder(b,from))
                    //None forward
                    return std::nullopt;
                if(pointsOrder(from, a) && pointsOrder(from, b))
                {
                    //Both forward
                    if(upper)
                        return input_polygon.at(a).y > input_polygon.at(b).y ? a : b;
                    else
                        //lower neighbour
                        return input_polygon.at(a).y < input_polygon.at(b).y ? a : b;
                    //TODO create a new point p which is the projection of the returned one on the other segment
                }
                //One forward
                return pointsOrder(a,b) ? b : a;
            };
            
            //Constructing the limits of the polygon
            std::vector<PointIndex> upperLimit;
            std::vector<PointIndex> lowerLimit;
            upperLimit.emplace_back(sweeping.at(0));
            lowerLimit.emplace_back(sweeping.at(0));
            for (long unsigned int i=1; i<sweeping.size(); i++)
            {
                const PointIndex sweeped = sweeping.at(i);
                const std::optional<PointIndex> nextForwardUpperPoint = nextForwardPoint(upperLimit.back(), true);
                const std::optional<PointIndex> nextForwardLowerPoint = nextForwardPoint(lowerLimit.back(), false);

                if(      nextForwardUpperPoint == std::nullopt
                      || *nextForwardUpperPoint == sweeped
                      || input_polygon.at(sweeped).y >= input_polygon.at(*nextForwardUpperPoint).y)
                {
                    upperLimit.emplace_back(sweeped);
                }

                if(      nextForwardLowerPoint == std::nullopt
                      || *nextForwardLowerPoint == sweeped
                      || input_polygon.at(sweeped).y <= input_polygon.at(*nextForwardLowerPoint).y)
                {
                    lowerLimit.emplace_back(sweeped);
                    std::cout << "Added sweeped : " << sweeped << ", nextForward : "  << (nextForwardLowerPoint == std::nullopt ? 1000 : *nextForwardLowerPoint) << std::endl;
                }
                else
                    std::cout << "Not added sweeped : " << sweeped << ", nextForward : "  << (nextForwardLowerPoint == std::nullopt ? 1000 : *nextForwardLowerPoint) << std::endl;
            }

            //Add points in counterclockwise order and avoid first and last duplicata
            std::vector<Point> resultPolygon;
            for (auto it = upperLimit.rbegin(); it != upperLimit.rend(); ++it)
                resultPolygon.emplace_back(input_polygon.at(*it));
            for (auto it = ++lowerLimit.begin(); it != --lowerLimit.end(); ++it)
                resultPolygon.emplace_back(input_polygon.at(*it));
            return resultPolygon;
        }
} //namespace chal


