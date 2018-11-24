#include <stdio.h>
#include <stdlib.h>

/*Creates Shape struct that then gets area and bounding box depending 
on the type of shape created*/

typedef struct
{
	double radius, originX, originY;
} Circle;

typedef struct
{
	double pt1X, pt2X, minY, maxY;
} Triangle;

typedef struct
{
	double minX, maxX, minY, maxY;
} Rectangle;

typedef struct
{
	void* self;
	void (*GetBoundingBox)(void *self, double *bbox);
	double (*GetArea)(void *self);
	
} Shape;


/*Area functions for each specific shape.*/
double GetCircleArea(void *circ)
{
	Circle *C = (Circle *) circ;
	double area = 3.14159*(C -> radius)*(C -> radius);
		
	return area;
};

double GetRectangleArea(void *rect)
{	
	Rectangle *R = (Rectangle *) rect;
	double area = ((R -> maxX)-(R -> minX))*((R -> maxY)-(R-> minY));
	
	return area;
};

double GetTriangleArea(void *tri)
{
	Triangle *T = (Triangle *) tri;
	double area = (((T -> pt2X)-(T -> pt1X))*((T -> maxY)-(T-> minY)))/2;

	return area;
};

/*Bounding box for specific shapes.*/
void GetCircleBoundingBox(void *circ, double *bbox)
{	
	Circle *C = (Circle *) circ;
	bbox[0] = (C -> originX) - (C -> radius);
	bbox[1] = (C -> originX) + (C -> radius);
	bbox[2] = (C -> originY) - (C -> radius);
	bbox[3] = (C -> originY) + (C -> radius);
};

void GetRectangleBoundingBox(void *rect, double *bbox)
{	
	Rectangle *R = (Rectangle *) rect;
	bbox[0] = R -> minX;
	bbox[1] = R -> maxX;
	bbox[2] = R -> minY;
	bbox[3] = R -> maxY;
};

void GetTriangleBoundingBox(void *tri, double *bbox)
{
	Triangle *T = (Triangle *) tri;
	bbox[0] = T -> pt1X;
	bbox[1] = T -> pt2X;
	bbox[2] = T -> minY;
	bbox[3] = T -> maxY;
};

/*Create functions for each specific shape.*/
Shape * CreateCircle(double radius, double originX, double originY)
{	Circle *circ;
	circ = malloc(sizeof(Circle));
	
	circ -> radius = radius;
	circ -> originX = originX;
	circ -> originY = originY;
	
	Shape * circ_shape;
	circ_shape = malloc(sizeof(Shape));
	
	circ_shape -> self = circ;
	circ_shape -> GetBoundingBox = GetCircleBoundingBox;
	circ_shape -> GetArea = GetCircleArea;
	
	
	return circ_shape;
};

Shape * CreateRectangle(double minX, double maxX, double minY, double maxY)
{	Rectangle *rect;
	rect = malloc(sizeof(Rectangle));
	rect -> minX = minX;
	rect -> maxX = maxX;
	rect -> minY = minY;
	rect -> maxY = maxY;
	
	Shape * rect_shape;
	rect_shape = malloc(sizeof(Shape));
	
	rect_shape -> self = rect;
	rect_shape -> GetBoundingBox = GetRectangleBoundingBox;
	rect_shape -> GetArea = GetRectangleArea;
	
	return rect_shape;
};

Shape * CreateTriangle(double pt1X, double pt2X, double minY, double maxY)
{	Triangle *tri;
	tri = malloc(sizeof(Triangle));
	tri -> pt1X = pt1X;
	tri -> pt2X = pt2X;
	tri -> minY = minY;
	tri -> maxY = maxY;
	
	Shape * tri_shape;
	tri_shape = malloc(sizeof(Shape));
	
	tri_shape -> self = tri;
	tri_shape -> GetBoundingBox = GetTriangleBoundingBox;
	tri_shape -> GetArea = GetTriangleArea;
	
	return tri_shape;
};

/*Gets each area from self of Shape.*/
double GetArea(Shape *s) {
	double area;
	area = s -> GetArea(s -> self);
	
	return area;
}
/*Gets each bounding box from self of Shape.*/
void GetBoundingBox(Shape *s, double *bbox) {
	s -> GetBoundingBox(s -> self, bbox);
}

int main()
{
    Shape *shapes[9];
    int    i;
    shapes[0] = CreateCircle(1, 0, 0);
    shapes[1] = CreateCircle(1.5, 6, 8);
    shapes[2] = CreateCircle(0.5, -3, 4);

    shapes[3] = CreateRectangle(0, 1, 0, 1);
    shapes[4] = CreateRectangle(1, 1.1, 10, 20);
    shapes[5] = CreateRectangle(1.5, 3.5, 10, 12);

    shapes[6] = CreateTriangle(0, 1, 0, 1);
    shapes[7] = CreateTriangle(0, 1, 0, 0.1);
    shapes[8] = CreateTriangle(0, 10, 0, 50);

    for (i = 0 ; i < 9 ; i++)
    {
        double bbox[4];
        printf("Shape %d\n", i);
        printf("\tArea: %f\n", GetArea(shapes[i]));
        GetBoundingBox(shapes[i], bbox);
        printf("\tBbox: %f-%f, %f-%f\n", bbox[0], bbox[1], bbox[2], bbox[3]);
		
		free(shapes[i]);
    }
}
