#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void showboard(int x1,int y1,int x2 ,int y2,int s, int **v, int **h, int *bwalls, int *wwalls) {
    printf("=\n");
    //prints letters
        printf("     ");
    for (int i = s; i >= 1; i--){
        char letter = (char)('A' - i + s);
        putchar(letter);
        printf("   ");
    }
    printf("\n");


    int temp = s;
    for(int i=0;i<(s);i++){
        printf ("   ");
        for(int k=0;k<s;k++) { //prints lines of +==== and +----
            if (h[temp][k] == 0 ) printf("+---");
            else if (h[temp][k] == 1) printf("+===");
        }
        printf("+\n");
        printf(" %d ",temp);
        for (int j=1;j<=(s);j++){ //prints lines of |   | and H   | etc and also prints W and B
            if (v[temp-1][j-1] == 1) printf("H ");
            else printf("| ");
            if (temp-1 ==x1 && j-1==y1) printf("W ");
            else if (temp-1 ==x2 && j-1==y2) printf("B ");
            else printf("  ");

        }

        printf("| %d \n",temp--);
    }
    printf("   ");
    for(int k=0;k<s;k++) {
        printf("+---");
    }
    printf("+\n");
    printf("     ");
    for (int i = s; i >= 1; i--){
        char letter = (char)('A' - i + s);
        putchar(letter);
        printf("   ");
    }
    printf("\nblack walls: %d \nwhite walls %d\n\n", *bwalls, *wwalls);

}

void clear_board(int** vwalls, int** hwalls, int size, int* i1, int* j1, int* i2, int* j2){
//SETS UP THE FOUR COORDINATES I1J1 - I2J2 FOR W AND B RESPECTIVELY
    *i2 = size -1;
    *j2 = size/2;
    *i1 = 0;
    *j1 = *j2;
    for (int i=0; i<size; i++){ // FILLS 2D ARRAY OF H(ORIZONTAL) AND V(ERTICAL) WALLS WITH 0
        for (int j=0; j<size; j++){
            vwalls[i][j]=0;
            hwalls[i][j]=0;
        }
    }
    printf("=\n\n");
}

void playwall(char color[], char placement[], char orientation[],int **V,int **H,int *bwalls,int *wwalls) {
    int j,i;
    char angle, xroma, letter;
    //CHECK TO SEE IF ENOUGH ARGUMENTS AND CONVERTS THEM
    if (placement != NULL && orientation != NULL && color != NULL){
        letter = toupper(placement[0]);
        i = atoi(&placement[1])-1;
        angle = toupper(*orientation);
        xroma = toupper(*color);
        j = (letter - 'A');
    }
    else {
        printf("?syntax error\n\n");
        fflush(stdout);
        return;
    }

    if (angle == 'V' ) {
        if (xroma == 'B'  && *bwalls > 0) {
            V[i][j+1] = 1;
            V[i - 1][j+1] = 1;
            (*bwalls)--;
            printf("=\n\n");
        } else if ((xroma == 'W') && *wwalls > 0) {
            V[i][j+1] = 1;
            V[i - 1][j+1] = 1;
            (*wwalls)--;
            printf("=\n\n");
        } else printf("?syntax error\n\n");
    }else if (angle == 'H') {
            if (xroma == 'W' && *bwalls > 0) {
                H[i][j] = 1;
                H[i][j + 1] = 1;
                printf("=\n\n");
                (*bwalls)--;
            }
            else if (xroma == 'B' && *wwalls > 0) {
                H[i][j] = 1;
                H[i][j + 1] = 1;
                printf("=\n\n");
                (*wwalls)--;
            }
            else printf("?syntax error\n\n");
        }
    else printf("?syntax error\n\n");
    }

void playmove(char clr[], char inp[],int s, int *i1, int *j1, int *i2, int *j2, int** V, int** H){
    int j,i;
    char xroma, letter;
    //CHECKS IF ENOUGH ARGUMENTS AND CONVERTS THEM
    if (inp != NULL && clr != NULL){
        letter = toupper(inp[0]);
        i = atoi(&inp[1])-1;
        xroma = toupper(clr[0]);
        j = (letter - 'A');
    }
    else {
        printf("?syntax error\n\n");
        fflush(stdout);
        return;
    }

 //TODO rewrite in a nicer way
 //CHECKS IF MOVE IS LEAGAL
            if (xroma == 'W' && i >=0 && i<s && j >=0 && j<s) {
                if (i - *i1 == 1 && j == *j1 && H[i][j] == 0) // move 1 up
                    *i1 = i;
                else if (i - *i1 == -1 && j == *j1 && H[*i1][*j1] == 0) // move 1 down
                    *i1 = i;
                else if (i == *i1 && j - *j1 == 1 && V[i][j+2] == 0) // move 1 right
                    *j1 = j;
                else if (i == *i1 && j - *j1 == -1 && V[i][j+1] == 0) // move 1 left
                    *j1 = j;
                else if (i - *i1 == 2 && j == *j1 && *i2 == (*i1 + 1) && H[*i1+1][j] == 0 && H[*i1 + 2][j] == 0) // jump over 2 up
                    *i1 = i;
                else if (i - *i1 == -2 && j == *j1 && *i1 == (*i2 + 1) && H[*i1 - 1][j] == 0 && H[*i1 - 2][j] == 0)//jump over 2 back
                    *i1 = i;
                else if (i == *i1 && j == *j1 + 2 && *j2 == *j1+1 && V[i][j]==0 && V[i][j+1]==0)//jump over 2 right
                    *j1=j;
                else if (i == *i1 && j == *j1 - 2 && *j1 == *j2 + 1 && V[i][j-1]==0 && V[i][j-2]==0)//jump 2 left
                    *j1 = j;
                else if ( (i == *i1 + 1 || i == *i1 - 1) && *i2 == *i1 && *j2 == *j1+1 && j == *j2 && V[*i2][*j2]==1 && V[*i1][*j1]==0){
                    *i1 = i;				                                			/* |   | * |   move to	*/
                    *j1 = j;							                                /* | W | B H   star (*) */
                }								                                        /* |   | * |		    */
                else if ( (i == *i1 + 1 || i == *i1 - 1) && *i2 == *i1 && *j1 == *j2+1 && j == *j2 && V[*i2][*j2-1] == 1) {

                    *i1 = i;                                                         /* | * |   |   move to  */
                    *j1 = j;                                                         /* H B | W |   star (*) */
                }                                                                    /* | * |   |            */

                else if (i == *i1 + 1 && i == *i2  && *j1 == *j2 && abs(j-*j1) == 1 && H[*i2+1][*j2]==1){
                    *i1 = i;                                                         /* |   |===|   | move to  */
                    *j1 = j;                                                         /* | * | B | * | star (*) */
                }                                                                    /* |   | W |   |          */
                else if (*j1 == *j2 && *i1 == *i2+1 && i == *i2+1 && abs(j-*j1)==1 && H[*i2][*j1] == 1 ){
                    *i1 = i;                                                         /* |   | W |   | move to  */
                    *j1 = j;                                                         /* | * | B | * | star (*) */
                }                                                                    /* |   |===|   |          */
            }
            else if (xroma == 'B' && i >=0 && i<s && j >=0 && j<s) {
                if (i - *i2 == 1 && j == *j2 && H[i][j] == 0) // move 1 up
                    *i2 = i;
                else if (i - *i2 == -1 && j == *j1 && H[*i2][*j2] == 0) // move 1 down
                    *i2 = i;
                else if (i == *i2 && j - *j2 == 1 && V[i][j+2] == 0) // move 1 right
                    *j2 = j;
                else if (i == *i2 && j - *j2 == -1 && V[i][j+1] == 0) // move 1 left
                    *j2 = j;
                else if (i - *i2 == 2 && j == *j2 && *i1 == (*i2 + 1) && H[*i2+1][j] == 0 && H[*i2 + 2][j] == 0) // jump over 2 up
                    *i2 = i;
                else if (i - *i2 == -2 && j == *j2 && *i2 == (*i1 + 1) && H[*i2 - 1][j] == 0 && H[*i2 - 2][j] == 0)//jump over 2 back
                    *i2 = i;
                else if (i == *i2 && j == *j2 + 2 && *j1 == *j2+1 && V[i][j]==0 && V[i][j+1]==0)//jump over 2 right
                    *j2=j;
                else if (i == *i2 && j == *j2 - 2 && *j2 == *j1 + 1 && V[i][j-1]==0 && V[i][j-2]==0)//jump 2 left
                    *j2 = j;
                else if ( (i == *i2 + 1 || i == *i2 - 1) && *i1 == *i2 && *j1 == *j2+1 && j == *j1 && V[*i1][*j1]==1 && V[*i2][*j2]==0){
                    *i2 = i;				                                			/* |   | * |   move to	*/
                    *j2 = j;							                                /* | B | W H   star (*) */
                }								                                        /* |   | * |		    */
                else if ( (i == *i2 + 1 || i == *i2 - 1) && *i1 == *i2 && *j2 == *j1+1 && j == *j1 && V[*i1][*j1-1] == 1) {

                    *i2 = i;                                                         /* | * |   |   move to  */
                    *j2 = j;                                                         /* H W | B |   star (*) */
                }                                                                    /* | * |   |            */

                else if (i == *i2 + 1 && i == *i1  && *j2 == *j1 && abs(j-*j2) == 1 && H[*i1+1][*j1]==1){
                    *i2 = i;                                                         /* |   |===|   | move to  */
                    *j2 = j;                                                         /* | * | W | * | star (*) */
                }                                                                    /* |   | B |   |          */
                else if (*j2 == *j1 && *i2 == *i1+1 && i == *i1+1 && abs(j-*j2)==1 && H[*i1][*j2] == 1 ){
                    *i2 = i;                                                         /* |   | B |   | move to  */
                    *j2 = j;                                                         /* | * | W | * | star (*) */
                }                                                                    /* |   |===|   |          */
            }
            else {
                printf("?syntax error\n\n");
                fflush(stdout);
                return;
            }
            printf("=\n\n");
            fflush(stdout);
            return;

}
void winner(int* i1, int*j1, int* i2, int* j2, int size) {


    if (*i1 == size - 1) {
        printf("=winner is white \n\n");
        fflush(stdout);
        return;
    } else if (*i2 == 0) {
        printf("=winner is black \n\n");
        fflush(stdout);
        return;
    } else {
        printf("?no winner yet \n\n");
        fflush(stdout);
    }
}

void name(){
            printf("=NOTIS - DREW\n\n");
            fflush(stdout);
            return;
        }
void genmove(char clr[], int* i1, int* j1, int* i2, int *j2,int s, int** H, int** V, int* reached_left){
    // OUR GENIUS STRATEGY: MOVE FORWARD AND IF NOT POSSIBLE LEFT
    // IF REACHED LEFT MOVE RIGHT WHILE EVERY TIME TRYING TO MOVE FORWARD
    char xroma = toupper(clr[0]);
    if (xroma == 'B') {
        if (*j2 == 0) {
            *reached_left = 1;
        }
        if (H[*i2][*j2] == 0 && *i2 - 1 >= 0){
            if (*i1 != *i2 - 1 || *j1 != *j2) {
                (*i2)--;
                *reached_left = 0;
            }
            else if (*i2 > 1 && H[*i1][*j2] == 0) {
                (*i2) -= 2;
            }
            else if (H[*i1-1][*j2]==1) {
                (*i2)--;
                (*j2) = (*j1-1);
            }
        }
        else if(*reached_left==0){
            if(V[*i2][*j2-1]==0) (*j2)--;
            else (*i2)--;
        }
        else if(*reached_left==1){
            if(V[*i2][*j2]==0) (*j2)++;
            else (*i2)--;
        }
    }
    else if (xroma == 'W') {
        if (*j1 == 0) {
            *reached_left = 1;
        }
        if (H[*i1+1][*j1] == 0 && *i1 +1 <= s){
            if (*i2 != *i1 + 1 || *j1 != *j2) {
                (*i1)++;
                *reached_left = 0;
            }
            else if (*i1 < s - 1 && H[*i1+2][*j2] == 0) {
                (*i1) += 2;
            }
            else if (H[*i1+2][*j2]==1) {
                (*i1)++;
                (*j1) = (*j2-1);
            }
        }
        else if(*reached_left==0){
            if(V[*i1][*j1-1]==0) (*j1)--;
            else (*i1)--;
        }
        else if(*reached_left==1){
            if(V[*i1][*j1]==0) (*j1)++;
            else (*i1)--;
        }
    }
    printf("=\n\n");
}





