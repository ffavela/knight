#include"headers.h"

int main(void)
{
	int tot = ROWS*COLS, mvnum = 1;
	int M[COLS][ROWS], mvchoice[tot+1];/*mvchoice[0] is not used... yet*/
	
/*Initialize the arrays*/
	Aones(mvchoice);
	M_init(M);

	while(mvnum < 64)
		mvnum = move(M, mvnum, mvchoice);

	printb(M);
	return 0;
}
