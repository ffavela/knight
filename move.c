/*mvmun returns 1 if succeds and 0 if it fails*/
#include"headers.h"

int n = 0, m = 0;

int move(int (*A)[ROWS], int mchoice, int mvmun, int rev)
{
	int icheck;

	icheck = check();	/*to change correctly m,n in either case*/

	if (rev == -1){
		A[m][n]=0;
		mvnum--;
		commit(m, n);
		return icheck;
	}

	commit();
	A[m][n]=mvmun++;
	return icheck;
}

int mm, nn; /*for use before commiting to the move*/

int check(){
	mm = m;
	nn = n;
	switch (mchoice){
		case 1:
			mm+=rev*2;
			nn+=rev*1;
			break;
		case 2:
			mm+=rev*1;
			nn+=rev*2;
			break;
		case 3:
			mm-=rev*1;
			nn+=rev*2;
			break;
		case 4:
			mm-=rev*2;
			nn+=rev*1;
			break;
		case 5:
			mm-=rev*2;
			nn-=rev*1;
			break;
		case 6:
			mm-=rev*1;
			nn-=rev*2;
			break;
		case 7:
			mm+=rev*1;
			nn-=rev*2;
			break;
		case 8:
			mm+=rev*2;
			nn-=rev*1;
			break;
		default:	/*it should not reach this point*/
			return 0;
			break;
	}

	if( ( mm < 0 || mm >= COLS) && (nn < 0 || nn >= ROWS) )/*check if it's within the board*/
		return 0;
}

void commit(void)
{
	&m = &mm;
	&n = &nn;
}
