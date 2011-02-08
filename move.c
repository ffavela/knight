/*mvmun returns 1 if succeds and 0 if it fails*/
#include"headers.h"

int move(int m, int n, int (*A)[ROWS], int mchoice, int mvmun, int rev)
{
	if (rev == -1)
		A[m][n]=0;

	check();
	if(rev == 1)
		A[m][n]=mvmun;

	return 1;
}

int check(){
	switch (mchoice){
		case 1:
			m+=rev*2;
			n+=rev*1;
			break;
		case 2:
			m+=rev*1;
			n+=rev*2;
			break;
		case 3:
			m-=rev*1;
			n+=rev*2;
			break;
		case 4:
			m-=rev*2;
			n+=rev*1;
			break;
		case 5:
			m-=rev*2;
			n-=rev*1;
			break;
		case 6:
			m-=rev*1;
			n-=rev*2;
			break;
		case 7:
			m+=rev*1;
			n-=rev*2;
			break;
		case 8:
			m+=rev*2;
			n-=rev*1;
			break;
		default:	/*it should not reach this point*/
			return 0;
			break;
	}

	if( ( m < 0 || m >= COLS) && (n < 0 || n >= ROWS) )
		return 0;
}
