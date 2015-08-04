/*
  Copyright (C) 2015 Francisco Favela

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include"headers.h"

int main(int argc, char *argv[])
{
	int m=0, n=0;
	int mvnum = 1, i=0;
	int M[ROWS][COLS], mvchoice[TOT+1];/*mvchoice[0] is not used... yet
	if(argc==3)
		m=atoi(argv[1])-1, n=atoi(argv[2])-1;
	
/*Initialize the arrays*/
	Aones(mvchoice);
	M_init(M, m, n);

	while(mvnum){
		while(mvnum < TOT)
			mvnum = move(M, mvnum, mvchoice, &m, &n);
		printb(M);
		printf("%d\n", ++i);
		while(mvnum == TOT)
			mvnum = move(M, mvnum, mvchoice, &m, &n);
		//mvchoice[--mvnum] = 9;
	}
	return 0;
}
