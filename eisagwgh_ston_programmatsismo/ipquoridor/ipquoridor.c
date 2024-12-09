#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ipq1.h"

int main() {
    int **V,  **H, *i1, *i2, *j1, *j2, s, *bwalls, *wwalls, *reached_left = 0;

    bwalls = malloc(sizeof(int));
    wwalls = malloc(sizeof(int));

    char inp[80];
    do {
        //GET INPUT
        fgets(inp, 79, stdin);
        char* p =  strtok(inp, " ");
        //SPLIT THE INP ON EVERY WHITESPACE
        //*p POINTS TO THE FIRST WORD
        //p = strtok(NULL, " ") MEANS MOVE POINTER TO THE NEXT WORD
        if (strcmp ( "boardsize",p) == 0) {
            p = strtok(NULL, " ");
            if (p == NULL){
                printf("?syntax error\n\n");
                fflush(stdout);
                continue;
            }
            //REMOVE THE \N FROM THE END OF P
            p = strtok(p,"\n");
            s = atoi(p);
            V = malloc((s) * sizeof(int *));
            if (V == NULL) {
                printf("?error\n\n");
                return -1;
            }
            for (int i=0;i <= (s); i++) {
                V[i] = malloc((s) * sizeof(int));
                if (*V == NULL) {
                    printf("can not allocate memory");
                    return -1;
                }
            }
            H = malloc((s) * sizeof(int *));
            if (H == NULL) {
                printf("can not allocate memory");
                return -1;
            }
            for (int i=0;i <= (s); i++) {
                H[i] = malloc((s) * sizeof(int));
                if (*H == NULL) {
                    printf("can not allocate memory");
                    return -1;
                }
            }
            printf("=\n\n");

        }else if (strcmp ("showboard\n",p) == 0) {
            showboard(i1, j1, i2, j2, s, V, H,bwalls, wwalls);
        }else if  (strcmp("clear_board\n",p) == 0) {
            clear_board(V, H, s, &i1, &j1, &i2, &j2);
        }else if  (strcmp("walls",p) == 0){
            p = strtok(NULL, " ");
            p = strtok(p,"\n");
            if (p == NULL || strlen(p)>1){
                printf("?syntax error\n\n");
                fflush(stdout);
                continue;
            }

            int num = atoi(p);
                *bwalls = num;
                *wwalls = num;
                printf("=\n\n");
                fflush(stdout);
        }else if  (strcmp("winner\n",p) == 0)
            winner(&i1, &j1, &i2, &j2, s);
        else if  (strcmp("undo",p) == 0){
                p = strtok(NULL, " ");
//                undo(atoi(p));
        }else if  (strcmp("genmove",p) == 0){
                p = strtok(NULL, " ");
                genmove(p, &i1, &j1, &i2, &j2, s, H, V, &reached_left);
        }else if  (strcmp("playwall",p) == 0){
                p = strtok(NULL, " ");
                char *color = p;
                p = strtok(NULL, " ");
                char *placement = p;
                p = strtok(NULL, " ");
                p = strtok(p,"\n");
                char *orientation = p;
                playwall(color, placement,orientation, V, H,bwalls,wwalls);
        }else if  (strcmp("playmove",p) == 0){
                p = strtok(NULL, " ");
                char *color = p;
                p = strtok(NULL, " ");
                char *place = p;
                playmove( color,  place, s,  &i1,  &j1,  &i2,  &j2,  V,  H);
        }
        else if (strcmp(p,"name\n")==0) name();
        else if  (strcmp("quit\n",p) == 0) {
            for (int i=0;i <= (s); i++){
                    free(V[i]);
                    free(H[i]);
            }
            free(V);
            free(H);
            printf("=/n/n");
            return 1;
        }
        else if (strcmp(p,"protocol_version\n")==0){
            printf("=0.1\n\n");
            fflush(stdout);
        }
        else if(strcmp(p, "version\n")==0){
            printf("= 0.0.1.notis.drew\n\n");
            fflush(stdout);
        }
        else if (strcmp(p,"list_commands\n")==0){
            printf("=\nprotocol_version\n"
                   "name\n"
                   "version\n"
                   "list_commands\n"
                   "quit\n"
                   "boardsize\n"
                   "clear_board\n"
                   "walls\n"
                   "genmove\n"
                   "playmove\n"
                   "playwall\n"
                   "winner\n"
                   "showboard\n\n");
        }
        else{
            printf("?syntax error\n\n");
            fflush(stdout);
            continue;
        }
    } while (1);

}