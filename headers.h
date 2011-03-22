#include<stdio.h>
#define COLS 8
#define ROWS 8

struct check_info
{
	int rev; /*for knowing if I should reverse commit etc.*/
	int mm, nn; /*for use before commiting to the move*/
};

void printb(int (*A)[COLS]);
void Aones(int *mvchoice);
void M_init(int (*A)[COLS], int m, int n);
int move(int (*A)[COLS], int mvmun, int mvchoice[]);
struct check_info check(int choice, int (*A)[COLS]);
void commit(void);
