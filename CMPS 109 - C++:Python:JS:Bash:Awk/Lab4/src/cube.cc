/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <array>

#include "cube.h"
#include "polygon.h"
#include "geom.h"
#include "reuleauxtriangle.h"
#include "circle.h"

Cube::Cube(Point3D upperFace[4], Point3D lowerFace[4]){
    for (unsigned int i =0; i < 4; i++) {
        upperFace_[i] = upperFace[i];
        lowerFace_[i] = lowerFace[i];
    }
}

std::array<Point3D, 4> Cube::upperFace() {
    return upperFace_;
}

std::array<Point3D, 4> Cube::lowerFace() {
    return lowerFace_;
}

std::vector<Line> Cube::edges() {
    std::vector<Line> edges;
    return edges;
}


bool Cube::containedWithin(Sphere &sphere) {
    return true;
}

bool Cube::containedWithin(Cube &cube) {
    return true;
}

bool Cube::containedWithin(ReuleauxTetrahedron &rt) {
    return true;
    
}
