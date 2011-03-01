#include"headers.h"

static int n = 0, m = 0, rev = 1; 

int move(int (*A)[COLS], int mvnum, int *mvchoice)
{
	rev = check(mvchoice[mvnum], A);
/*rev ordered by occurrence*/
	if(rev == 1){
		commit();
		A[m][n]=++mvnum;
	}else if(rev == 0){
		rev =  1;/*so that there's no trouble in check*/
		mvchoice[mvnum]++;
	}else{	/*that is rev == -1, move back*/
		A[m][n]=0;
		mvchoice[mvnum--]=1;/*so the move is not default in check*/
		rev = check(mvchoice[mvnum], A);/*That is rev=1*/
		++mvchoice[mvnum];	
		commit();
	}
	return mvnum;
}

int mm, nn; /*for use before commiting to the move*/
/*returns 1 if ok to move, 0 if it can't and -1 if it must move back*/
int check(int choice, int (*A)[COLS]){
	mm = m;
	nn = n;
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

void commit(void)
{
	m = mm;
	n = nn;
}

void M_init(int (*A)[COLS])
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
