/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <string>

#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"


//Function for printing test results to console
static void testResults(const std::string testType, bool testKey, bool attempt) {
    std::cout << testType;
    if (testKey == attempt) {
        std::cout << "PASS\n";
    }
    else
        std::cout << "FAIL\n";
}

//Testing Circles within Circles
static void circleInCircle() {
    //Create outer Circle
    Circle outer = Circle(Point2D(0.0,0.0), 8.0);
    
    for (int i=-1; i<=1; i+=2) {
        for (int j=-1; j<=1; j+=2) {
            Circle inner = Circle(Point2D(i*1.0,j*1.0), 4.0);
            testResults("Circle-in-Circle: ", true, inner.containedWithin(outer));
            
            //Move inner circle
            inner.setCenter(Point2D(i*3.0,j*7.0));
            testResults("Circle-Overlapping-Circle: ", false, inner.containedWithin(outer));
            
            //Move inner circle again
            inner.setCenter(Point2D(i*17.0,j*17.0));
            testResults("Circle-Outside-Circle: ", false, inner.containedWithin(outer));
        }
    }
}
//Testing Triangles within Circles
static void triangleInCircle(){
    //Create shapes
    Circle outer = Circle(Point2D(0.0,0.0), 8.0);

    for (int i=-1; i<=1; i+=2) {
        for (int j=-1; j<=1; j+=2) {
            RegularConvexPolygon inner = RegularConvexPolygon({
                Point2D(i*1,j*1), Point2D(i*2,j*2),Point2D(i*3,j*1)} );
            
            testResults("Triangle-in-Circle: ",true, inner.containedWithin(outer));
            
            //Move and test
            inner = RegularConvexPolygon({Point2D(i*1,j*7), Point2D(i*2,j*9),Point2D(i*3,7)});
            testResults("Triangle-Overlapping-Circle: ",false, inner.containedWithin(outer));
            
            //Move and test
            inner = RegularConvexPolygon({Point2D(i*0,j*10), Point2D(i*12,j*5),Point2D(i*15,j*0)});
            testResults("Triangle-Outside-Circle: ",false, inner.containedWithin(outer));

        }
    }
}
static void squareTests() {
    //Create Shapes
    RegularConvexPolygon outer = RegularConvexPolygon({
        Point2D(-10,10), Point2D(10,10),
        Point2D(10,-10), Point2D(-10,-10)} );
    for (int i=-1; i<=1; i+=2) {
        for (int j=-1; j<=1; j+=2) {
            //Setup and test:
            RegularConvexPolygon inner = RegularConvexPolygon({
                Point2D(i*1,j*2), Point2D(i*2,j*2),
                Point2D(i*2,j*1), Point2D(i*1,j*1)} );
            testResults("Square-in-Square: ",true, inner.containedWithin(outer));
            
            //Move and test
            inner = RegularConvexPolygon({
                Point2D(i*8,j*2), Point2D(i*11,j*2),
                Point2D(i*11,j*1), Point2D(i*8,j*1)} );
            testResults("Square-Overlapping-Square: ",false, inner.containedWithin(outer));
            
            //Move and test
            inner = RegularConvexPolygon({
                Point2D(i*11,j*6), Point2D(i*15,j*6),
                Point2D(i*15,j*2), Point2D(i*11,j*2)} );
            testResults("Square-Outside-Square: ",false, inner.containedWithin(outer));
        }
    }
    
}
static void circularTests(){
    circleInCircle();
    triangleInCircle();
}
int main(int argc, char *argv[]) 
{
    circularTests();        //Actually do the testing
    squareTests();
    
    RegularConvexPolygon inner = RegularConvexPolygon({
        Point2D(-10,10), Point2D(10,10),
        Point2D(10,-10), Point2D(-10,-10)} );
    Point2D vertices[3] = { Point2D(0,12.32),Point2D(10,-5),Point2D(-10,-5) };
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    
    testResults("Square-in-Reuleaux: ",false, inner.containedWithin(outer));
    
    Circle cInner = Circle(Point2D(-12,0),4.0);
    testResults("Circle-in-Reuleaux: ",false, cInner.containedWithin(outer));
    
    
    
}
