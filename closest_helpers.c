#include "closest_helpers.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int verbose = 0;

int compare_x(const void* a, const void* b) 
{
    int x1 = ((struct Point *)a)->x;
    int x2 = ((struct Point *)b)->x;
    if (x1 < x2){
        return -1;
    } else if (x1 > x2){
        return 1;
    } else{
        return 0;
    }
} 

int compare_y(const void* a, const void* b) 
{ 
    int y1 = ((struct Point *)a)->y;
    int y2 = ((struct Point *)b)->y;
    if (y1 < y2){
        return -1;
    } else if (y1 > y2){
        return 1;
    } else{
        return 0;
    }
} 

double dist(struct Point p1, struct Point p2) 
{
    unsigned long long x = pow((long long)p1.x-p2.x, 2);
    unsigned long long y = pow((long long)p1.y-p2.y, 2);
    return (double)sqrt(x+y);
} 
