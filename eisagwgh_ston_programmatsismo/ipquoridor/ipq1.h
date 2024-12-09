void clear_board(int** vwalls, int** hwalls, int size, int* i1, int* j1, int* i2, int* j2);
void showboard(int x1,int y1,int x2 ,int y2,int s, int **v, int **h, int*, int*);
boardsize(int size);
void walls(int num, int * bwalls, int* wwalls);
void winner(int* i1, int*j1, int* i2, int* j2, int size);
void playwall(char *color, char *placement, char * orientation,int **V,int **H,int *bwalls,int *wwalls );
void playmove(char* color, char* inp,int s, int *i1, int *j1, int *i2, int *j2, int** V, int** H);
void name();
void genmove(char clr[], int* i1, int* j1, int* i2, int *j2,int s, int** H, int** V, int*);