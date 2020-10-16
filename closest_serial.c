#include "closest_serial.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h> //perror

double combine_lr(struct Point P[], size_t n, struct Point mid_point, double d)
{
    struct Point arr[n];
    int curr_i = 0;
    
    for (size_t i = 0; i < n; i++){
        if (abs(P[i].x - mid_point.x) < d) {
            arr[curr_i] = P[i];
            curr_i++;
        }
    }
    double distance = dist(arr[0], arr[1]);
    qsort(arr, curr_i, sizeof(struct Point), compare_y);
    for (size_t i = 0; i < curr_i; i++){
        for (size_t j = i + 1; j< curr_i; j++){
            if (arr[i].y - arr[j].y < d){
                if (dist(arr[i], arr[j]) < distance){
                    distance = dist(arr[i], arr[j]);
                }
            }
        }
    }
    return fmin(d, distance);
}

double _closest_serial(struct Point P[], size_t n)
{
    int mid = floor(n/2);
    struct Point midpoint = P[mid];
    double dl;
    double dr;
    double d;
    if (mid <= 3){

        dl = brute_force(P, mid);
    } else{
        dl = _closest_serial(P, mid);
    }
    if (n-mid <= 3){
        dr = brute_force(P+mid, n-mid);
    } else{
        dr = _closest_serial(P+mid, n-mid);
    }

    d = combine_lr(P, n, midpoint, fmin(dl, dr));
    return fmin(fmin(dr, dl), d);
}

double closest_serial(struct Point P[], size_t n)
{
    qsort(P, n, sizeof(struct Point), compare_x);
    return _closest_serial(P, n);
}
