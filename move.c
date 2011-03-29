#include"headers.h"

int move(int (*A)[COLS], int mvnum, int *mvchoice, int *pm, int *pn)
{
	int rev = 1, test;
	INFO info;

	info = check(mvchoice[mvnum], A, *pm, *pn, rev);
/*rev ordered by occurrence*/
	if((rev = info.rev) == 1){
		A[info.mm][info.nn]=++mvnum;
		if(64 - mvnum > MAXDEPTH)/*so rcheck won't block finishing*/
			if(!rcheck(A, MAXDEPTH, info.mm, info.nn))
				mvchoice[mvnum] = 9;/*Move back!!*/
		commit(info, pm, pn);
	}else if(rev == 0){
		rev =  1;/*so that there's no trouble in check*/
		mvchoice[mvnum]++;
	}else{	/*that is rev == -1, move back*/
		A[*pm][*pn]=0;
		mvchoice[mvnum--]=1;/*so the move is not default in check*/
		info = check(mvchoice[mvnum], A, *pm, *pn, rev);/*That is rev=1*/
		++mvchoice[mvnum];	
		commit(info, pm, pn);
	}
	return mvnum;
}

/*in rev it returns 1 if ok to move, 0 if it can't and -1 if it 
 * must move back, additionaly returns the tentative 
 * new position (mm, nn)*/
INFO check(int choice, int (*A)[COLS], int m, int n, int rev){
	INFO report;
	int *mm = &report.mm, *nn = &report.nn;
	 *mm = m;
	 *nn = n;
	switch (choice){
		case 1:
			*mm+=rev*2;
			*nn+=rev*1;
			break;
		case 2:
			*mm+=rev*1;
			*nn+=rev*2;
			break;
		case 3:
			*mm-=rev*1;
			*nn+=rev*2;
			break;
		case 4:
			*mm-=rev*2;
			*nn+=rev*1;
			break;
		case 5:
			*mm-=rev*2;
			*nn-=rev*1;
			break;
		case 6:
			*mm-=rev*1;
			*nn-=rev*2;
			break;
		case 7:
			*mm+=rev*1;
			*nn-=rev*2;
			break;
		case 8:
			*mm+=rev*2;
			*nn-=rev*1;
			break;
		default:	
			report.rev = -1;
			return report;
			break;
	}
	/*check if it's within the board and if the square is free*/
	if(*mm < 0 || *mm >= COLS || *nn < 0 || *nn >= ROWS || A[*mm][*nn] != 0)
		report.rev = 0;
	else
		report.rev = 1;
	return report;
}
/*checks recursively, returns 1 if ok, 0 if not*/
int rcheck(int (*A)[COLS], int depth, int rm, int rn)
{
	int choices, rmult = 1, rsum = 0;
	INFO info;

	if(depth == 0)
		return 1;/*if reached here then it reached a tip and it's not isolated*/

	for(choices = 1; choices <= MAXCHOICE; choices++){
		info = check(choices, A, rm, rn, TRUE_REV);
		if( info.rev == 1){/*Note: if it can't move then rmult & rsum are preserved*/
			A[info.mm][info.nn] = depth - MAXDEPTH - 1;/*using neg # to fill array*/
			rmult*=rcheck(A, depth-1, info.mm, info.nn);
			A[info.mm][info.nn]=0;/*every level cleans up after themselves*/
			rsum+=1;/*to know if it actually made a move*/
		}/*if rmult=0 then there was at least 1 isolated square*/
	}/*if rsum=0 then there was no moves in the respective depth*/
	if(rmult == 0 || rsum == 0 && depth != MAXDEPTH)/*if depth=MAXDEPTH&&sum=0, ok*/
		return 0;/*if it made it here then it's a dead end*/
	return 1;/*if it's here then it's not a tip and this branch is not isolated*/
}

void commit(INFO info, int *pm, int *pn)
{
	*pm = info.mm;
	*pn = info.nn;
}

void M_init(int (*A)[COLS], int m, int n)
{
	int i, j;

	for(j = 0; j < ROWS; j++)
		for(i = 0; i < COLS; i++)
			A[i][j] = 0;

	A[m][n] = 1;
}

void Aones(int *mvchoice)
{
	int k;
	for(k = 0; k < 64; k++)
		mvchoice[k] = 1;
}

void printb(int (*M)[COLS])
{
	int i,j;
	for(j = 1; j <= ROWS; j++){
		for(i = 0; i < COLS; i++)
			printf("%3d", M[i][ROWS-j]);
		printf("\n");
	}
}
