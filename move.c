/*
  Copyright (C) 2015 Francisco Favela

  This file is part of knight

  knight is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  knight is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include"headers.h"

int move(int (*A)[COLS], int mvnum, int *mvchoice, int *pm, int *pn)
{
	int rev = 1, test;
	INFO info;

	info = check(mvchoice[mvnum], A, *pm, *pn, rev);
/*rev ordered by occurrence*/
	if((rev = info.rev) == 1){
		A[info.mm][info.nn]=++mvnum;
		if(TOT - mvnum > MAXDEPTH)/*so RocKTopus won't block finishing*/
			if(!RocKTopus(A, MAXDEPTH, info.mm, info.nn))
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
 * new position (mm, nn), also it returns 2 for RocKTopus (when A[*mm][*nn]<0)*/
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
	if(*mm < 0 || *mm >= COLS || *nn < 0 || *nn >= ROWS || A[*mm][*nn] > 0)
		report.rev = 0;
	else if (A[*mm][*nn] == 0)
		report.rev = 1;
	else /* that is A[*mm][*nn]<0 */
		report.rev = 2;
	return report;
}
/*The recursive octopus function (RocKtopus)*/
/*checks recursively, returns 1 if ok, 0 if not*/
int RocKTopus(int (*A)[COLS], int depth, int rm, int rn)
{
	int choices, rmult = 1, rsum = 0, negs = 0;
	INFO info;

	if(depth == 0)
		return 1;/*it reached a tip and it's not isolated*/
/*Note: if it can't move then rmult & rsum are preserved*/
	for(choices = 1; choices <= MAXCHOICE; choices++){
		info = check(choices, A, rm, rn, TRUE_REV);
		if(info.rev == 1){
			A[info.mm][info.nn] = depth-MAXDEPTH-1;/*using neg # to fill array*/
			rmult*=RocKTopus(A, depth-1, info.mm, info.nn);
			A[info.mm][info.nn]=0;/*every level cleans up after themselves*/
			rsum++;/*to know if it actually made a move*/
			if(!rmult)/*for parallelizing put cond. outside the for*/
				return 0;
		}else if(info.rev==2)/*if rmult=0 then there was at least 1 isolated square*/
			negs++;/*it can't move there because of its trayectory*/
	}/*if rsum=0 then there were no moves in the respective depth*/
	if(depth != MAXDEPTH)
		if(rmult > 1)/*also implies that rsum >= 1. Note: rmult<=2**rsum */
			return test(rmult, rsum);/*either 2 or 1*/
		else if(rsum)/*remembering that here rmult=1*/
			return 1;
		else if(negs > 1)/*reached a frustrated tip(rsum=0)*/
			return 2;
		else/*rsum=0 && negs=1*/
			return 0;/*dead end*/
	if(rmult > 1 && test(rmult, rsum) == 2)/*here depth=MAXDEPTH*/
		return 0;/*no escape from this route*/
	return 1;/*it's not a tip and this branch is not isolated*/
}/*Note: rsum=0 && depth=MAXDEPTH it's ok*/
/*Note: in the end it always returns either 0 or 1*/
void commit(INFO info, int *pm, int *pn)
{
	*pm = info.mm;
	*pn = info.nn;
}

void M_init(int (*A)[COLS], int m, int n)
{
	int i, j;

	for(j = 0; j < COLS; j++)
		for(i = 0; i < ROWS; i++)
			A[i][j] = 0;

	A[m][n] = 1;
}

void Aones(int *mvchoice)
{
	int k;
	for(k = 0; k < TOT; k++)
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
/*returns 1 if there is a way out or 2 if it's not yet found*/
test(int num, int tot)
{
	while(num && tot--)
		num/=2;
	if(num)/*the move possibilities lead to self frustration*/
		return 2;
	return 1;/*there's at least one choice with no frustration*/
}
