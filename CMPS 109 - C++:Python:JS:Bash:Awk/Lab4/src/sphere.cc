/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <array>

#include "sphere.h"
#include "circle.h"
#include "polygon.h"
#include "geom.h"
#include "reuleauxtriangle.h"

Sphere::Sphere(Point3D center, double radius) {          //take const Point2D arg to be cautious
    setCenter(center);
    setRadius(radius);
}

Point3D Sphere::center() {
    return center_;
}

void Sphere::setCenter(const Point3D &center) {
    center_.x = center.x;
    center_.y = center.y;
    center_.z = center.z;
}

double Sphere::radius() {
    return radius_;
}

void Sphere::setRadius(double radius) {
    radius_ = radius;
}

/*
 * If distance between centers is less than difference between the radius of containing 
 * circle and the radius of this circle, this circle is not contained
 */
bool Sphere::containedWithin(Sphere &sphere) {
    return true;
}

/*
 * If circle intersects with any polygon edge, circle is not contained       
 * If line between centers intersects with any polygon edge, circle is not contained
 * Only other possibility is that the circle is contained
 */
bool Sphere::containedWithin(Cube &cube)
{

    return true;
}

bool Sphere::containedWithin(ReuleauxTetrahedron &rt) {
    return true;
}
