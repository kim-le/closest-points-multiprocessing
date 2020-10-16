#include "closest_parallel.h"
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <math.h>


int curr_depth = 0; //know when to stop creating processes

double _closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
    static int num_forks = 0; // total number of forks
    double dl;
    double dr;
    double d;
    *pcount = 0;

    //pdmax = the maximum depth of the process tree
    if(n < 4 || pdmax == 0){
        return _closest_serial(P, n);
    }

    int mid = floor(n/2);
    struct Point midpoint = P[mid];
    pid_t left, right;
    int lfd[2], rfd[2];
    if (pipe(lfd) < 0){
        perror("pipe");
        exit(1);
    }
    
    if (!(left = fork())) {
        //left
        curr_depth++;
        pdmax--;
        close(lfd[0]);
        dl = _closest_parallel(P, mid, pdmax, pcount);
        write(lfd[1], &dl, sizeof(double));
        close(lfd[1]);
        exit(num_forks);
    } else if (left > 0){
        //parent
        if (pipe(rfd) < 0){
            perror("pipe");
            exit(1);
        }     
        if (!(right = fork())) {
            //right
            curr_depth++;
            pdmax--;
            close(rfd[0]);
            dr = _closest_parallel(P+mid, n-mid, pdmax, pcount);
            write(rfd[1], &dr, sizeof(double));
            close(rfd[1]);
            exit(num_forks);
        } else if (right > 0) {
            //parent
            close(lfd[1]);
            close(rfd[1]);
            int lstat, rstat;
            if (wait(&lstat) == -1){
                perror("wait");
                exit(1);
            } 
            if (wait(&rstat) == -1){
                perror("wait");
                exit(1);
            }
            if (WIFEXITED(lstat)){
                num_forks += WEXITSTATUS(lstat);
            }
             if (WIFEXITED(rstat)){
                num_forks += WEXITSTATUS(rstat);
            }
            num_forks+=2;
            //if (curr_depth ==0){
            *pcount += num_forks; 
            //} 
            read(lfd[0], &dl, sizeof(double));
            read(rfd[0], &dr, sizeof(double));
            close(lfd[0]);
            close(rfd[0]);
            //printf("%d %d %d\n", curr_depth, *pcount, num_forks);
            d = combine_lr(P, n, midpoint, fmin(dl, dr));
    
            return fmin(fmin(dr, dl), d);
        } else{
            perror("fork");
            exit(1);
        }
    } else {
        perror("fork");
        exit(1);
    }
}

double closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
    qsort(P, n, sizeof(struct Point), compare_x);
    return _closest_parallel(P, n, pdmax, pcount);
}
