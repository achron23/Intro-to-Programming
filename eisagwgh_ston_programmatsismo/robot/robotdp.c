#include "robotrec.h"
#include <stdlib.h>

int maxnum(int a, int b){
    if (a > b) return a;
    else return b;
}


void path(int n,int m,int **A,int **dp){
    char x;
    if(n==0 && m==0){
        if(A[n][m]==1) x='C';
        else x='.';
        printf(" %c(%d,%d)/%d -->", x,n+1,m+1, dp[n][m]);
        return;
    }
    if(n==0){
        path(n,m-1, A, dp);										      //if n=0 the previous cell of the path is (n,m-1)

    }
    else if(m==0){
        path(n-1, m, A, dp);										      //if m=0 the previous cell of the path is (n-1,m)

    }
    else{
        if(dp[n - 1][m] > dp[n][m - 1]) path(n - 1, m, A, dp);				     //the previous cell of the path is the one that has the largest dp number
        else path(n,m-1, A, dp);

    }
    if(A[n][m]==1) x='C';
    else x='.';
    printf(" %c(%d,%d)/%d -->", x,n+1,m+1, dp[n][m]);	//prints the content of the cell,the coordinates of the cell and the number of coins the robot has taken so far
    return;
}



int solve(int n, int m, int **A){
    int i, j;
    int **dp,coins;
    dp = malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        printf("Sorry, cannot allocate memory\n");
        return -1;
    }
    for (i=0 ; i <= n; i++) {
        dp[i] = malloc((m + 1) * sizeof(int));
        if (dp[i] == NULL) {
            printf("Sorry, cannot allocate memory\n");
            return -1;
        }
    }
    for (i = 0; i <= n; i++){
        for (j = 0; j<=m; j++){
            if (i == 0 && j == 0) {
                dp[i][j] = A[i][j];
            } else if (i == 0) {
                dp[i][j] = A[i][j] + dp[i][j-1];
            } else if (j == 0) {
                dp[i][j] = A[i][j] + dp[i-1][j];
            } else {
                dp[i][j] = A[i][j] + maxnum(dp[i][j-1] , dp[i-1][j]);
            }
        }
    }
    coins=dp[n][m];
    printf("\nPath is:");
    path(n, m, A, dp);
    printf("\nPicked up %d coins", coins);
    for (i = 0; i <= n; i++)                                      //free allocated memory
        free(dp[i]);
    free(dp);
    return coins;
}

