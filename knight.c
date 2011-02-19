#include<stdio.h>
#include"headers.h"

int main(void)
{
	int tot = ROWS*COLS, mvnum = 1;
	int M[COLS][ROWS], mvchoice[tot];
	
/*Initialize the arrays*/
	Aones(mvchoice);
	Mzeroes(M[ROWS][COLS]);

	while(mvmun != tot)
		mvnum = move((*M)[COLS], mvnum);

	printb((*M)[COLS]);
	return 0;
}
