/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <array>

#include "polygon.h"
#include "geom.h"
#include "reuleauxtriangle.h"
#include "circle.h"

RegularConvexPolygon::RegularConvexPolygon(std::vector<Point2D> vertices) {
    vertices_ = vertices;
}

std::vector<Point2D> RegularConvexPolygon::vertices() {
    return vertices_;
}

std::vector<Line> RegularConvexPolygon::edges() {
    std::vector<Line> edges;
    for (unsigned int i = 0; i < vertices_.size()-1; i++) 
        edges.push_back(Line(vertices_[i],vertices_[i+1]));
    edges.push_back(Line(vertices_[vertices_.size()-1],vertices_[0]));
    return edges;
}

int RegularConvexPolygon::vertexCount() {
    return vertices_.size();
}

bool RegularConvexPolygon::containedWithin(Circle &circle) {
    std::vector<Point2D> vertices = this->vertices();       //Get Triangle points
    if (Geom::distance(Geom::center(*this), circle.center()) >
                        circle.radius()) {
        return false;
    }
    for (unsigned int i = 0; i < vertices.size(); i++) {
        if (Geom::distance(vertices.back(),circle.center()) > circle.radius()) {
            return false;
        }
        else
        vertices.pop_back();
    }
    return true;
}

bool RegularConvexPolygon::containedWithin(RegularConvexPolygon &polygon) {
    //Get all the outer edges into a vector
    std::vector<Line> outerEdges = polygon.edges();
    //Get line from the center of the two polygons;
    Line polyDistance = Line(Geom::center(*this),Geom::center(polygon));
    
    //Check to see if any edges of the polygons intersect
    for (unsigned int i=0; i<=outerEdges.size(); i++) {           //For each outer edge...
        if (Geom::intersects(outerEdges.back(), polyDistance ) ) {
            //std::cout << "Center Line Fail";
            return false;                               //...Outside completely?
        }
        //Get all the inner edges into a vector
        std::vector<Line> innerEdges = this->edges();
        for (unsigned int j=0; j<=innerEdges.size(); j++) {       //...Intersects any inner?
            if (Geom::intersects(outerEdges.back(),innerEdges.back() )) {
                //std::cout << "Edge Line Fail";
                return false;
            }
            else
                innerEdges.pop_back();                  //get next inner edge
        }
        outerEdges.pop_back();                          //get next outer edge
    }
    //else polygon is contained
    return true;
}

bool RegularConvexPolygon::containedWithin(ReuleauxTriangle &rt) {
    //Get the edges of the inner polygon
    std::vector<Line> innerEdges = this->edges();
    std::array<Point2D,3> rVertices = rt.vertices();
    double sideLength = Geom::distance(rVertices[0],rVertices[1]);
    
    for (unsigned int i =0; i <3; i++) {
        Circle outer = Circle(rVertices[i], sideLength);
        if (this->containedWithin(outer) ) {
            //check next circle
            continue;
        }
        else
            return false;
    }

    return true;
    
}
