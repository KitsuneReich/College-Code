/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include "containable.h"
#include "point.h"
#include "polygon.h"

class Sphere : public Containable3D {               //Inherits all the public traits of Containable
    private:
        Point3D center_;
        double radius_;

    public:
        // do not change this constructor
        Sphere(Point3D center, double radius);

        Point3D center();
        void setCenter(const Point3D &center);

        double radius();
        void setRadius(double radius);

    //These *must* be implemented per Containable
    bool containedWithin(Sphere &sphere) = 0;
    bool containedWithin(Cube &cube) = 0;
    bool containedWithin(ReuleauxTetrahedron &rt) = 0;
};
