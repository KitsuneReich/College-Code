/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <vector>
#include <array>

#include"reuleauxtriangle.h"
#include "polygon.h"
#include "geom.h"

ReuleauxTriangle::ReuleauxTriangle(Point2D vertices[3]) {
    vertices_[0] = vertices[0];
    vertices_[1] = vertices[1];
    vertices_[2] = vertices[2];
}

std::array<Point2D,3> ReuleauxTriangle::vertices() {
    return vertices_;
}

bool ReuleauxTriangle::containedWithin(Circle &circle) {
    std::array<Point2D,3> rVertices = this->vertices();
    double sideLength = Geom::distance(rVertices[0],rVertices[1]);
    
    if (sideLength < circle.radius() ) {
        RegularConvexPolygon inner = RegularConvexPolygon({ rVertices[0], rVertices[1], rVertices[2] });
        if (inner.containedWithin(*this)) {
            return true;
        }
        else
            return false;
        }
    else
        return false;
}

bool ReuleauxTriangle::containedWithin(RegularConvexPolygon &polygon) {
    return true;
}

bool ReuleauxTriangle::containedWithin(ReuleauxTriangle &rt) {
    return true;
}
