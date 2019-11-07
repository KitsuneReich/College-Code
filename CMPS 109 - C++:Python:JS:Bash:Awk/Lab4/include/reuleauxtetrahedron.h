/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <vector>
#include<array>

#include "containable.h"
#include "point.h"
#include "circle.h"
#include "line.h"

// C++ requires forward declaration of any cyclically dependent classes
class Circle;
class RegularConvexPolygon;

class ReuleauxTetrahedron : public Containable3D {
    private:
        std::array<Point3D,4> vertices_;

    public:
        ReuleauxTetrahedron(Point3D vertices[4]);
        std::array<Point3D,4> vertices();

        bool containedWithin(Sphere &sphere);
        bool containedWithin(Cube &cube);
        bool containedWithin(ReuleauxTetrahedron &rt);
};
