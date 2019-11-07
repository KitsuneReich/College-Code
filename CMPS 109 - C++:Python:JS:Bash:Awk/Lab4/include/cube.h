/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <vector>
#include <array>

#include "containable.h"
#include "point.h"
#include "circle.h"
#include "line.h"

// C++ requires forward declaration of any cyclically dependent classes
class Cube;

class Cube : public Containable3D {
    private:
        std::array<Point3D,4> upperFace_, lowerFace_;

    public:
        // do not change this constructor
        Cube(Point3D upperFace[4], Point3D lowerFace[4]);

        std::array<Point3D, 4> upperFace();
        std::array<Point3D, 4> lowerFace();
        std::vector<Line> edges();

    bool containedWithin(Sphere &sphere);
    bool containedWithin(Cube &cube);
    bool containedWithin(ReuleauxTetrahedron &rt);
};
