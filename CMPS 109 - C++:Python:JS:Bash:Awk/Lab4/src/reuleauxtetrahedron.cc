/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <vector>
#include <array>

#include "reuleauxtetrahedron.h"
#include"reuleauxtriangle.h"
#include "polygon.h"
#include "geom.h"

ReuleauxTetrahedron::ReuleauxTetrahedron(Point3D vertices[4]) {
    for (unsigned int i = 0; i < 5; i++) {
        vertices_[i] = vertices[i];
    }
}

std::array<Point3D,4> ReuleauxTetrahedron::vertices() {
    return vertices_;
}

bool ReuleauxTetrahedron::containedWithin(Sphere &sphere) {
    return true;
}

bool ReuleauxTetrahedron::containedWithin(Cube &cube) {
    return true;
}

bool ReuleauxTetrahedron::containedWithin(ReuleauxTetrahedron &rt) {
    return true;
    
}
