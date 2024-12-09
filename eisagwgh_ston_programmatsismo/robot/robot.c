#include <stdio.h>
#include <stdlib.h>
#include "robotrec.h"


int main(void){
    int n;
    int m;
    int ch;
    int **A;
    scanf("%d",&n);
    scanf("%d",&m);
    A = malloc(n * sizeof(int*));
    if (A == NULL) {
        printf("Sorry, cannot allocate memory\n");
        return -1;
    }
    for (int j = 0; j < n; j++) {
        A[j] = malloc(m * sizeof (int));
        if (A[j] == NULL) {
            printf("Sorry, cannot allocate memory\n");
            return -1;
        }
    }
    int i=0;
    int j=0;
    int flag=0;
    while ((ch = getchar()) != EOF ){       //filling my array with 1 and 0
        if(i==n)
        {
            break;
        }
        if (ch == '.') {
            A[i][j] = 0;
            j++;
        } else if (ch == 'C') {
            A[i][j] = 1;
            j++;
        } else if (ch == '\n') {
            if(flag==0) {
                flag = 1;
                continue;
            }
            j = 0;
            i++;
        }

    }
    n--;
    m--;
    int coins= solve(n, m, A);
    if (coins == -1)
        printf("ERROR");
    for(j=0 ; j<n ; j++){
        free (A[j]);
    }
    free (A);
}


























































/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "robotrec.h"

int main(void) {
    int ch;
    int i = 0;
    int j = 0;
    int nm = 0;
    char c;
    int n = 0;
    int m = 0;
    int temp;
    int **A;
    int pr = 0;
    while ((ch = getchar()) != EOF) {
        if (nm == 0) {
            if (ch == ' ') {
                nm = 1;
                pr = 0;
                printf("%d\n", n);
                A = malloc(n * sizeof *A);
            } else {
                c = ch;
                temp = c - '0';
                n = n + pow(temp, pr);
                pr++;
            }
        } else if (nm == 1) {
            if (ch == ' ') {
                nm = 2;
                printf("%d\n", m);
                for (j = 0; j < n; j++) {
                    A[j] = malloc(m * sizeof *A[j]);
                }
                j = 0;
            } else {
                c = ch;
                temp = c - '0';
                m = m + pow(temp, pr);
                pr++;
            }
        } else {
            if (ch == '.') {
                A[i][j] = 0;
                j++;
            } else if (ch == 'C') {
                A[i][j] = 1;
                j++;
            } else if (ch == '\n') {
                j = 0;
                i++;
            }
        }
    }
    */
/* for (i = 0; i < n; i++) {
         for (j = 0; j < m; j++) {
             printf("%d \t", A[i][j]);
         }
         printf("\n");
     }*//*

    //int paths = robotmem( n,  m,  **A);
    //printf("thesd;afkj is %d \n", paths);

}
*/
