#include"headers.h"

int main(void)
{
	int m = 0, n = 0;
	int tot = ROWS*COLS, mvnum = 1;
	int M[COLS][ROWS], mvchoice[tot+1];/*mvchoice[0] is not used... yet*/
	
/*Initialize the arrays*/
	Aones(mvchoice);
	M_init(M, m, n);

	while(mvnum < 50)
		mvnum = move(M, mvnum, mvchoice, &m, &n);

	printb(M);
	return 0;
}
