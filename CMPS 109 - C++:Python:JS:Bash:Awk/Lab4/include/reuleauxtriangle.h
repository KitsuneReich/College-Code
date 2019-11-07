/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#ifndef _REULEAUXTRIANGLE_H_
#define _REULEAUXTRIANGLE_H_

#include <vector>
#include<array>

#include "containable.h"
#include "point.h"
#include "circle.h"
#include "line.h"

// C++ requires forward declaration of any cyclically dependent classes
class Circle;
class RegularConvexPolygon;

class ReuleauxTriangle : public Containable2D {
    private:
        std::array<Point2D,3> vertices_;

    public:
        ReuleauxTriangle(Point2D vertices[3]);
        std::array<Point2D,3> vertices();

        bool containedWithin(Circle &circle);
        bool containedWithin(RegularConvexPolygon &polygon);
        bool containedWithin(ReuleauxTriangle &rt);
};

#endif
