#include"headers.h"

int main(int argc, char *argv[])
{
	int m=0, n=0;
	int mvnum = 1, i=0;
	int M[ROWS][COLS], mvchoice[TOT+1];/*mvchoice[0] is not used... yet*/
	if(argc==3)
		m=atoi(argv[1])-1, n=atoi(argv[2])-1;
	
/*Initialize the arrays*/
	Aones(mvchoice);
	M_init(M, m, n);

	while(TRUE){
		while(mvnum < TOT && mvnum) 
			mvnum = move(M, mvnum, mvchoice, &m, &n);
		if(!mvnum)
			break;
		printb(M);
		printf("%d\n", ++i);
		while(mvnum == TOT)
			mvnum = move(M, mvnum, mvchoice, &m, &n);
	//	mvchoice[--mvnum] = 9;
	}
	return 0;
}
