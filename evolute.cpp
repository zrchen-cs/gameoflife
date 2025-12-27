#include "common.h"
#include "myrand.h"
#include<stdlib.h>
#include<algorithm>
#include<math.h> 
using namespace std;

int max(int x,int y){
	if(x>y) return x;
	else return y;
}

int min(int x,int y){
	if(x<y) return x;
	else return y;
}

int init_state(int current[COL][ROW], int col, int row) {
	int i, j;
	
	init_rand();
	
	for (i = 0; i < col; i++)
		for (j = 0; j < row; j++)
			current[i][j] = zero_or_one(10);
}

int calc_result(int current[COL][ROW], int col, int row) {
	int result, i, j;
	
	for (i = 0; i < col; i++)
		for (j = 0; j < row; j++)
			result += current[i][j];
			
	return result;
}

void log_result(int target[COL][ROW], int current[COL][ROW], int col, int row) {
	int i, j;
	
	for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++)
	    	target[i][j] = current[i][j];
}

int check_dup(int target[COL][ROW], int current[COL][ROW], int col, int row) {
	int i, j;
	
	for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++)
	    	if (target[i][j] != current[i][j]) return 0;
	    	
	return 1;	      
}

int check_dup_all(int logs[ROUND][COL][ROW], int current[COL][ROW], int col, int row, int round) {
	int i, j, r;
	
	for (r = 0; r < round; r++)
		if (check_dup(logs[r], current, col, row)) return 1;
	
	return 0;	
}

int getval(int current[COL][ROW], int col, int row, int i, int j) {
	if (i >= 0 && i < col && j >= 0 && j < row) return current[i][j];
	else return 0;
}

void changeij(int current[COL][ROW], int next[COL][ROW], int col, int row, int i, int j) {

	int val = getval(current, col, row, i, j), count = 0;
	
	count += getval(current, col, row, i - 1, j - 1);
	count += getval(current, col, row, i, j - 1);
	count += getval(current, col, row, i + 1, j - 1);
	count += getval(current, col, row, i - 1, j);
	count += getval(current, col, row, i + 1, j);
	count += getval(current, col, row, i - 1, j + 1);
	count += getval(current, col, row, i, j + 1);
	count += getval(current, col, row, i + 1, j + 1);
	
	if (val == 0) {
		if (count == 3) next[i][j] = 1;
	}
	else {
		if (count == 2 || count == 3) next[i][j] = 1;
		else next[i][j] = 0;
	}
}

void makenext(int a[COL][ROW], int b[COL][ROW], int col, int row) {
	int next, i, j;

	for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++)
	       changeij(a, b, col, row, i, j);
	       
    for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++)
	      a[i][j] = b[i][j];
}

int try_count(int a[COL][ROW], int d, int col, int row) {
	int count_value = 0;
	for(int i = max(0, col - d); i <= min(COL, col + d); i++)
		for(int j = max(0, row - d); j <= min(ROW, row + d); j++){
			count_value += a[i][j];
		}
	return count_value; 
}

void makedecision(int a[COL][ROW], int b[COL][ROW], int col, int row,int d,int standard){
	int i[9] = {abs(try_count(a, d, col - 1, row - 1) - standard), abs(try_count(a, d, col - 1, row) - standard), abs(try_count(a, d, col - 1, row + 1) - standard),
	            abs(try_count(a, d, col, row - 1)     - standard), abs(try_count(a, d, col, row)     - standard), abs(try_count(a, d, col, row + 1)     - standard),
			    abs(try_count(a, d, col + 1, row - 1) - standard), abs(try_count(a, d, col + 1, row) - standard), abs(try_count(a, d, col + 1, row + 1) - standard)};
	int k[9] = {0};
	
	if (col == 0) {  
		i[0] = 10000;
		i[1] = 10000;
		i[2] = 10000;
	}
	if (col == COL - 1) {
		i[6] = 10000;
		i[7] = 10000;
		i[8] = 10000;
	}
	if (row == 0) {
		i[0] = 10000;
		i[3] = 10000;
		i[6] = 10000;
	}
	if (row == ROW - 1) {
		i[2] = 10000;
		i[5] = 10000;
		i[8] = 10000;
	}
	if (col > 0) {
		if (row > 0 && a[col - 1][row - 1]) i[0] = 10001;
		if (a[col - 1][row]) i[1] = 10001;
		if (row < ROW - 1 && a[col - 1][row + 1]) i[2] = 10001;
	}
    if (row > 0 && a[col][row - 1]) i[3] = 10001;
	if (row < ROW - 1 && a[col][row + 1]) i[5] = 10001;	
	if (col < COL - 1){
		if(row > 0 && a[col + 1][row - 1]) i[6] = 10001;
		if(a[col + 1][row]) i[7] = 10001;
		if(row < ROW - 1 && a[col + 1][row + 1]) i[8] = 10001;
	}
	
	for (int j = 0; j < 9 && j != 4; j++) {
		k[j] = i[j];
	}
	k[4] = i[4];
	
	sort(i, i + 9);
	
	for (int j = 4; j < 9; j++) if (k[j] == i[0]) {
		b[col][row]--;
		b[col + j / 3 - 1][row + j % 3 - 1]++;
		return;
	}
	for (int j = 0; j < 4; j++) if (k[j] == i[0]) { 
		b[col][row]--;
		b[col + j / 3 - 1][row + j % 3 - 1]++;
		return;
	}
}

void makenext_move(int a[COL][ROW], int b[COL][ROW], int col, int row, int d, int standard) {
	int next, i, j;

	for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++)
	       changeij(a, b, col, row, i, j);
	       
    for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++)
	      a[i][j] = b[i][j];
	
    for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++){
	    	if(a[i][j] == 1) makedecision(a, b, i, j, d, standard); 
		}
			
    for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++){
	    	if(b[i][j] > 1) b[i][j] = 1; 
		}
			
    for (i = 0; i < col; i++)
	    for (j = 0; j < row; j++)
	      a[i][j] = b[i][j];
}


