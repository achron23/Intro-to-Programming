#include "robotrec.h"

void minrobots(int n, int m, int **A){
    int i,j,robotcoins,flag;
    char cdot;
    int coins=0,robots=0;
    for(i=0;i<=n;i++){
        for(j=0;j<=m;j++){
            if (A[i][j]==1)
                coins++;
        }
    }
    int coinsleft=coins;
    while (coinsleft!=0){
        robots++;
        robotcoins=0;
        i=0;
        j=0;
        printf("\nRobot %d: ",robots);
        while (i<=n && j<=m) {
            if (A[i][j] == 1) {
                robotcoins++;
                coinsleft--;
                A[i][j] = 0;
                cdot = 'C';
            } else
                cdot = '.';
            printf("%c(%d,%d)%d --> ", cdot, i + 1, j + 1, robotcoins);
            if (i == n)
                j++;
            else if (j == m)
                i++;
            else {
                flag=0;
                for(int z=i+1;z<m;z++){
                    if(A[z][j] == 1){
                        flag=1;
                        break;
                    }
                }
                if (flag==1)
                    i++;
                else
                    j++;
            }
        }
        printf("\nPicked up %d coin(s)",robotcoins);

    }
    printf("\n%d robots picked up %d coins",robots,coins);
}


int solve(int n, int m, int **A){
    minrobots(n,m,A);
    return 1;
}
