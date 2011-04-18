#include<stdio.h>
#include<stdlib.h>
#define COLS 	8
#define ROWS	8
#define TOT		(ROWS)*(COLS)
#define MAXCHOICE	8
#define MAXDEPTH	2/*amount of times RocKtopus is called, use at least 2*/
#define TRUE_REV	1

struct check_info
{
	int rev; /*for knowing if I should reverse the commit etc.*/
	int mm, nn; /*for use before commiting to the move*/
};
typedef struct check_info INFO;

void printb(int (*A)[COLS]);
void Aones(int *mvchoice);
void M_init(int (*A)[COLS], int m, int n);
int move(int (*A)[COLS], int mvmun, int mvchoice[], int *pm, int *pn);
struct check_info check(int choice, int (*A)[COLS], int m, int n, int rev);
void commit(struct check_info info, int *pm, int *pn);
int RocKtopus(int (*A)[COLS], int depth, int rm, int rn);
int test(int rmult, int rsum);
