#include"headers.h"

int move(int (*A)[COLS], int mvnum, int *mvchoice, int *pm, int *pn)
{
	struct check_info info;
	info = check(mvchoice[mvnum], A, pm, pn);
/*rev ordered by occurrence*/
	if((rev = info.rev) == 1){
		commit(pm);
		A[m][n]=++mvnum;
	}else if(rev == 0){
		rev =  1;/*so that there's no trouble in check*/
		mvchoice[mvnum]++;
	}else{	/*that is rev == -1, move back*/
		A[m][n]=0;
		mvchoice[mvnum--]=1;/*so the move is not default in check*/
		rev = check(mvchoice[mvnum], A, pm, pn);/*That is rev=1*/
		++mvchoice[mvnum];	
		commit();
	}
	return mvnum;
}

/*in rev returns 1 if ok to move, 0 if it can't and -1 if it must move back
 * additionaly returns the tentative new position (mm, nn)*/
struct check_info check(int choice, int (*A)[COLS], pm, pn){
	struct check_info report;
	int *mm , *nn;
	report.mm = *mm = *pm;
	report.nn = *nn = *pn;
	switch (choice){
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
		default:	
			return -1;
			break;
	}
	/*check if it's within the board and if the square is free*/
	if(  mm < 0 || mm >= COLS || nn < 0 || nn >= ROWS || A[mm][nn] != 0)
		return 0;
	return 1;
}

void commit(int *from_m, int *to_m, int *from_n, int *to_n)
{
	to__m = from_m;
	to_n = from_n;
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
