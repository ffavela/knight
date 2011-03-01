#include<stdio.h>
#define COLS 8
#define ROWS 8

void printb(int (*A)[COLS]);
void Aones(int *mvchoice);
void M_init(int (*A)[COLS]);
int move(int (*A)[COLS], int mvmun, int mvchoice[]);
int check(int choice, int (*A)[COLS]);
void commit(void);
