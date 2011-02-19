#define COLS 8
#define ROWS 8

printb(int (*A)[COLS]);
void Aones(int *mvchoice)
void Mzeroes(int (*A)[COLS]);
int move(int m, int n, int (*A)[COLS], int mvmun);
int check(int mchoice, int (*A)[COLS]);
void commit(void);
