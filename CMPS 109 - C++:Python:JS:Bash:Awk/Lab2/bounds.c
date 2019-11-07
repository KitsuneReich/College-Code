#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bounds.h"

static Shape *target;

/*
 * Intialise a two or thre dimensional space of shape ARENA containing NUMSHAPES 
 * SHAPES, all of which may or may not be entirely contained within ARENA.
 */
void setup(Shape *a, Shape *shapes[], int numShapes) {
	target = a; 
}
static bool isCircleInsideCircle(Circle *target, Circle *dart){
	float distance = sqrt(
		pow((target->center.x - dart->center.x),2) +
		pow((target->center.y - dart->center.y),2)
	);
	return distance <= target->radius - dart->radius;
}
static bool isCircleInsideSquare(Polygon *target, Circle *dart){
	float sideLength = abs(target->vertices[1].x);	//a side of the square 
	float distanceX = (abs(dart->center.x) + dart->radius);
	float distanceY = (abs(dart->center.y) + dart->radius);
	return (distanceX <= sideLength && distanceY <= sideLength);	
}
static bool isSquareInsideCircle(Circle *target, Polygon *dart){
	int max = dart->numVertices;			//for each vertex:
	for(int i = 0; i < max; i++){
		printf("%f\n",dart->vertices[i].x);
		if( (abs(dart->vertices[i].x) > target->radius) ||
		    (abs(dart->vertices[i].y) > target->radius) ){
			printf("Outside\n");
			return false;
		}
	}
	return true;
}
/*
 * Move SHAPE to POINT. 
 *
 * Return TRUE if SHAPE remains entirely within the space defined by the 
 * ARENA parameter of setup(), FALSE otherwise.
 */
bool move(Shape *shape, Point *point) {
	if(target->type == CIRCLE) {
		if(shape->type == CIRCLE){	
		Circle *dart = (Circle *) shape;
		dart->center.x = point->x;			//Move center
		dart->center.y = point->y;	
		return isCircleInsideCircle((Circle *)target, dart);	//check
		}
		else if(shape->type == POLYGON){
		Polygon *dart = (Polygon *) shape;
		float sideLength = abs(dart->vertices[1].x);
		float diagonal = ((sqrt(2) * sideLength) * .5);
		
		int max = dart->numVertices;			//for each vertex:
		for(int i = 0; i < max; i++){
			float x = dart->vertices[i].x;
			float y = dart->vertices[i].y;

			if (x >= 0){
				dart->vertices[i].x += (diagonal);
			}
			else if (x < 0){
				dart->vertices[i].x -= (diagonal);
			}
			  
			if (y < 0){
				dart->vertices[i].x -= (diagonal);
			}
			else if (y >= 0){
				dart->vertices[i].x += (diagonal);
			}
		}	
		return isSquareInsideCircle((Circle *)target, dart);
		}
	}
	else if(target->type == POLYGON && shape->type == CIRCLE){
		Circle *dart = (Circle *) shape;
		dart->center.x = point->x;
		dart->center.y = point->y;	
		return isCircleInsideSquare((Polygon *)target, dart);
	}
	return false;
}
