#define COLS 8
#define ROWS 8

int move(int m, int n, int (*A)[ROWS], int mchoice, int mvmun, int rev);
int check(int mchoice, int rev);
void commit(void);
