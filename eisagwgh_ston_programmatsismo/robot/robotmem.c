#include "robotrec.h"
#include <stdlib.h>


int maxnum(int a, int b){
    if (a > b) return a;
    else return b;
}

int robotmem(int n, int m,int **mem, int **A) {
    if (mem[n][m] == -1) {
        if (n == 0 && m == 0) {
            mem[n][m] = A[n][m];
        } else if (n == 0) {
            mem[n][m] = A[n][m] + robotmem(n, m - 1, mem, A);
        } else if (m == 0) {
            mem[n][m] = A[n][m] + robotmem(n - 1, m, mem, A);
        } else {
            mem[n][m] = A[n][m] + maxnum(robotmem(n - 1, m, mem, A), robotmem(n, m - 1, mem, A));
        }
    } else {
        return mem[n][m];
    }
}

void path(int n,int m,int **A,int **mem){
    char x;
    if(n==0 && m==0){
        if(A[n][m]==1) x='C';
        else x='.';
        printf(" %c(%d,%d)/%d -->", x,n+1,m+1, mem[n][m]);
        return;
    }
    if(n==0){
        path(n,m-1, A, mem);										      //if n=0 the previous cell of the path is (n,m-1)

    }
    else if(m==0){
        path(n-1, m, A, mem);										      //if m=0 the previous cell of the path is (n-1,m)

    }
    else{
        if(mem[n - 1][m] > mem[n][m - 1]) path(n - 1, m, A, mem);				     //the previous cell of the path is the one that has the largest mem number
        else path(n,m-1, A, mem);

    }
    if(A[n][m]==1) x='C';
    else x='.';
    printf(" %c(%d,%d)/%d -->", x,n+1,m+1, mem[n][m]);	//prints the content of the cell,the coordinates of the cell and the number of coins the robot has taken so far
    return;
}


int solve(int n, int m, int **A){
    int i, j;
    int **mem,coins;
    mem = malloc((n+1) * sizeof(int *));
    if (mem == NULL) {
        printf("Sorry, cannot allocate memory\n");
        return -1;
    }
    for (i=0 ; i <= n; i++){
        mem[i] = malloc((m+1) * sizeof(int));
        if (mem[i] == NULL) {
            printf("Sorry, cannot allocate memory\n");
            return -1;
        }
        for (j=0 ; j <= m ; j++){
            mem[i][j] = -1;
        }
    }
    coins=robotmem(n, m, mem, A);
    printf("\nPath is:");
    path(n,m,A,mem);
    printf("\nPicked up %d coins",coins);
    for(i=0; i<=n; i++)								      //free allocated memory
        free(mem[i]);
    free (mem);
    return coins;
}