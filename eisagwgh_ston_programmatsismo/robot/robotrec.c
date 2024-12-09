#include "robotrec.h"


int maxnum(int a, int b){
    if (a > b) return a;
    else return b;
}

int rec(int n, int m, int **A){
    if (n == 0 &&  m== 0)
        return A[n][m];
    else if (n == 0 )
            return A[n][m] + rec(n, m - 1, A);
    else if (m == 0 )
            return A[n][m] + rec(n - 1, m, A);
    else{
        return maxnum(rec(n - 1, m, A) , rec(n, m - 1, A)) + A[n][m];

    }
}

int solve(int n,int m, int **A){
    int coins;
    coins=rec(n,m,A);
    printf("\nMaximum number of coins to pick up is:%d",coins);
    return coins;
}