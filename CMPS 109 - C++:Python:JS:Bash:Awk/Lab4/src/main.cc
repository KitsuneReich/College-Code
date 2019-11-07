/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

//Code sourced/altered from https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=2be08498-8350-4514-b8fe-06e265820e39

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"
#include "cube.h"
#include "sphere.h"
#include "reuleauxtetrahedron.h"

#define USAGE "USAGE %s test-file\n"

static Point2D getPoint(std::string &token) {
    double x,y;
    std::stringstream vstream(token);
    std::string value;
    
    if (std::getline(vstream, value, ',')) {
        std::stringstream(value) >> x;
        if (std::getline(vstream, value, ',')) {
            std::stringstream(value) >> y;
            return Point2D(x,y);
        }
    }
    throw "invalid point" + token;
}

static double getRadius(std::string &token) {
    return std::stod(token);            //string to double on the token
}

static void parse(const std::string line) {
    std::stringstream stream(line);
    std::string token;
    
    Circle *inner = NULL;           //Initialize shapes
    Circle *outer = NULL;
    RegularConvexPolygon *pInner = NULL;
    RegularConvexPolygon *pOuter = NULL;
    bool expected = false;
    std::string text;
    
    
    //getline gets the next token on a stringstream
    //geline gets next line on a filestream
    while (stream >> token) {
        if (token.front() == '#') {         //Comments not needed
            return;
        }
        
        if (token == "Circle" ) {
            stream >> token;        //extract a token from the line
            Point2D center = getPoint(token);
            stream >> token;        //next token off the line
            double radius = getRadius(token);
            if (inner == NULL && pInner == NULL) {  //check to see if inner
                inner = new Circle(center, radius); //is a Polygon
            }
            else {
                outer = new Circle(center, radius);
            }
        }
        if (token == "RegularConvexPolygon") {
            std::vector<Point2D> vertices;
            for (unsigned int i=0; i < 4; i++) {    //Load up vertices vector
                stream >> token;
                Point2D point = getPoint(token);
                vertices.push_back(point);
            }
            if (pInner == NULL && inner == NULL) {
                pInner = new RegularConvexPolygon(vertices);
            }
            else {
                pOuter = new RegularConvexPolygon(vertices);
            }
        }
        if (token == "true") {      //Only need to change if true
            expected = true;
            getline(stream, text);
        }
    }
    
    //Check to see which shapes are NULL, then test appropriately
    //Circle in circle
    if (pInner == NULL && pOuter == NULL) {
        bool got = inner->containedWithin(*outer);
        std::cout << (got == expected ? "PASS " : "FAIL ") << text <<std::endl;
    }
    //square inside circle
    if (pInner != NULL && outer != NULL) {
        bool got = pInner->containedWithin(*outer);
        std::cout << (got == expected ? "PASS " : "FAIL ") << text <<std::endl;

    }
}

int main(int argc, char *argv[]) 
{

    if (argc < 2) {
        printf(USAGE, argv[0]);
        return -1;
    }
    
    std::cout << "Test file: " << argv[1] << std::endl;
    
    std::ifstream inputFile(argv[1]);
    if (inputFile) {
        std::string line;
        while (std::getline(inputFile, line)) {
            //std::cout << line << std::endl;
            parse(line);
        }
    }
    return 0;
}
