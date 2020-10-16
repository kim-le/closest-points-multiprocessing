#include "closest_brute.h"
#include <stdio.h>
#include <math.h>

double brute_force(struct Point P[], size_t n) 
{ 
    if (n <= 1){
        return INFINITY;
    }
    double closest = dist(P[0], P[1]);
    if (n == 2){
        return closest;
    }
    for (size_t i = 0; i < n; i ++){
        for (size_t j = i + 1; j < n; j++){
            if (closest > dist(P[i], P[j])){
                closest = dist(P[i], P[j]);
            }
        }
    }
    return closest; 
} 
