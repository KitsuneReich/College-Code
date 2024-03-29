/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <array>

#include "circle.h"
#include "polygon.h"
#include "geom.h"
#include "reuleauxtriangle.h"

Circle::Circle(const Point2D &center, double radius) {          //take const Point2D arg to be cautious
    setCenter(center);
    setRadius(radius);
}

Point2D Circle::center() {
    return center_;
}

void Circle::setCenter(const Point2D &center) {
    center_.x = center.x;
    center_.y = center.y;
}

double Circle::radius() {
    return radius_;
}

void Circle::setRadius(double radius) {
    radius_ = radius;
}

/*
 * If distance between centers is less than difference between the radius of containing 
 * circle and the radius of this circle, this circle is not contained
 */
bool Circle::containedWithin(Circle &circle) {
    return Geom::distance(center(), circle.center()) <= (circle.radius() - radius());
}

/*
 * If circle intersects with any polygon edge, circle is not contained       
 * If line between centers intersects with any polygon edge, circle is not contained
 * Only other possibility is that the circle is contained
 */
bool Circle::containedWithin(RegularConvexPolygon &polygon) 
{
    for (Line const &edge: polygon.edges()) {
        if (Geom::intersects(edge, *this)) 
            return false;
    }

    Line line(Geom::center(polygon), center_);
    for (Line const &edge: polygon.edges()) {
        if (Geom::intersects(edge, line))
            return false;
    }

    return true;
}

bool Circle::containedWithin(ReuleauxTriangle &rt) {
    std::array<Point2D,3> rVertices = rt.vertices();
    double sideLength = Geom::distance(rVertices[0],rVertices[1]);
    
    for (unsigned int i =0; i <3; i++) {
        Circle outer = Circle(rVertices[i], sideLength);
        if (this->containedWithin(outer) ) {
            //check next circle
            continue;
        }
        else
            return false;
    }
    return true;
}
