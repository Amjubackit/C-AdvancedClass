// Course: Advanced C programming
// exercise 1, question 2
// file name: ex1_q2.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --------------------------- //


// --------------------------- //
// function declaration and main section:
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
    #include "ex1_q2.h"
#else
    #define FUNC_DECLARE

    // struct declaration section:
    typedef struct point
    {
        int x, y;
    }point;

    typedef struct polygon
    {
        int n;
        point * points;
        double scope;
    }polygon;
    // --------------------------- //

    unsigned long student_id();
    void scanPoint(point*);
    void scanPolygon(polygon*);
    double distance(point*, point*);
    void calculatePolygonScope(polygon*);
    void freeMemory(polygon*);

    int main()
    {
        unsigned long id_num;
        polygon poly;
        
        // call functions:
        id_num = student_id();
        printf("[id: %lu] start main\n", id_num);
        
        scanPolygon(&poly);
        calculatePolygonScope(&poly);
        freeMemory(&poly);
    
        // write output:
        printf("Output: Scope of polygon: %.2lf\n", poly.scope);
        
        return 0;
    }
#endif
// --------------------------- //


// --------------------------- //
// function implementation section:
unsigned long student_id()
{
    // return your id number,
    // for example if your id is 595207432
    // return 595207432
    // your code:
    return 313586869;

}
// --------------------------- //


/// <summary>
/// Function scan a point in the plane,
/// Used as auxiliary function for createPolygon.
/// </summary>
/// <param>point* p - pointer to p</param>
/// <returns>None</returns>
void scanPoint(point* p)
{
    // your code:
    printf("Enter point (x y): ");
    scanf("%d%d", &p->x, &p->y);
    printf("Scanned point: (%d,%d)\n", p->x, p->y);
}
// --------------------------- //


/// <summary>
/// Function scan a polygon with n verticies,
/// Example of input parameters:
/// 4 1 2 2 3 3 2 2 1
/// translate to 4 points with values: 
/// (1,2), (2,3), (3,2), (2,1) 
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>None</returns>
void scanPolygon(polygon* poly)
{
    // your code:
    puts("Enter number of points:");
    scanf("%d" ,&poly->n);

    // Allocating enough memory for desired points.
    poly->points = (point*)malloc(sizeof(point)*poly->n);
    // Scanning points using scanPoint() function.
    for (int i = 0; i<poly->n; i++) {
        scanPoint(poly->points + i);
    }
}
// --------------------------- //


/// <summary>
/// Function calculates distance between 2 adjacent points  
/// </summary>
/// <param>point* p1 - pointer to the first point</param>
/// <param>point* p2 - pointer to the second point</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
double distance(point* p1, point* p2)
{
    // your code:
    double width_squared, height_squared;
    width_squared = pow((double) (p1->x - p2->x), 2);
    height_squared = pow((double) (p1->y - p2->y), 2);
    // Returns distance between points
    return sqrt(width_squared + height_squared);
}
// --------------------------- //


/// <summary>
/// Function calculates the Scope of the entire polygon.
/// Setting the result inside the polygon object.  
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>None</returns>
void calculatePolygonScope(polygon* poly)
{
    // your code:
    poly->scope = 0;
    // Calculating distance between all points including last point & first point
    for (int i = 0; i < poly->n; i++) {
        poly->scope += distance(poly->points + i, poly->points + (i + 1) % poly->n);
    }
}
// --------------------------- //


/// <summary>
/// Function free allocated memory.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>None</returns>
void freeMemory(polygon* poly)
{
    // your code:
    if (poly->points == NULL) {
        return;
    }
    free(poly->points);
}
// --------------------------- //
