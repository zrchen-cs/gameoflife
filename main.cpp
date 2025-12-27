#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "evolute.h"
#include "display.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void help(char * appname) {
	char * p = appname + strlen(appname) - 1;
	while (p >= appname) {
		if (*p == '\\' || *p == '/') break;
		p--;
	}
		
	printf("The command line of %s should be one of the following cases: \n", p + 1);
	printf("  %s ori <max_iter_everytime> <times>\n", p + 1);
	printf("  %s try <max_iter_everytime> <max_d>\n", p + 1);
	printf("  %s set <max_iter_everytime> <d> <rational_count> <times>\n", p + 1);
	exit(0);
}

void print_settings(int cmd_idx, char * cmd, int max_iter, int col, int row, int set_d, int set_rational_count, int times_main, int max_d_main) {
	printf("settings: cmd=%s, max_iter_everytime=%d, col=%d, row=%d", cmd, max_iter, col, row);
	if (cmd_idx == CMD_ORI) printf(", times=%d\n", times_main);
	else if (cmd_idx == CMD_TRY) printf(", max_d=%d\n", max_d_main); 
	else if (cmd_idx == CMD_SET) printf(", set_d=%d, set_rational_count=%d, times=%d\n", set_d, set_rational_count, times_main);
	else printf("\n");
}

int main(int argc, char * argv[]) {
	char * cmd;
	int cmd_idx = CMD_ORI;
	int max_iter_main = 300;
	int times_main = 10;
	int max_d_main = 5;
	int set_d_main = 2;
	int set_rational_count_main = 2;
	
	int iter, i_time, total, result;
	
	if (argc < 3) help(argv[0]);
	
	cmd = argv[1];
	if (strcmp(cmd, "ori") == 0) cmd_idx = CMD_ORI;
	else if (strcmp(cmd, "try") == 0) cmd_idx = CMD_TRY;
	else if (strcmp(cmd, "set") == 0) cmd_idx = CMD_SET;
	else help(argv[0]);
	
	max_iter_main = atoi(argv[2]);
	if (max_iter_main <= 0) help(argv[0]);
	
	switch (cmd_idx) {
		case CMD_ORI:
			if (argc < 4) help(argv[0]);
			times_main = atoi(argv[3]);
			if (times_main <= 0) times_main = 1;
			break;
		case CMD_TRY:
			if (argc < 4) help(argv[0]);
			max_d_main = atoi(argv[3]);
			if (max_d_main <= 0) help(argv[0]);
			break;
		case CMD_SET:
			if (argc < 6) help(argv[0]);
			set_d_main = atoi(argv[3]);
			set_rational_count_main = atoi(argv[4]);
			times_main = atoi(argv[5]);
			if (set_d_main <= 0) help(argv[0]);
			if (set_rational_count_main <= 0) help(argv[0]);
			if (times_main <= 0) times_main = 1;
			break;
	}
	
	print_settings(cmd_idx, cmd, max_iter_main, COL, ROW, set_d_main, set_rational_count_main, times_main, max_d_main);	
	
	switch (cmd_idx) {
		case CMD_ORI:
			i_time = times_main;
			
			total = 0;
			
			do {
				int state[COL][ROW] = {{0}};
				int temp[COL][ROW] = {{0}};
				int logs[ROUND][COL][ROW] = {{{0}}};
				int idx = 0;
				
				printf("#%d ", times_main - i_time + 1);

				init_screen();
				
				init_state(state, COL, ROW);
				
				iter = max_iter_main;
				
				do {
					print_screen(max_iter_main - iter + 1, state);
					makenext(state, temp, COL, ROW);

					if (check_dup_all(logs, state, COL, ROW, ROUND)) break;
					
					log_result(logs[idx], state, COL, ROW);
					
					idx = (idx + 1) % ROUND;
				} while(--iter);
				
				result = calc_result(state, COL, ROW);
				total += result;
				
				printf("result = %d (stopped at iter %d)\n", result, max_iter_main - iter);
				
				cleanup_screen();
			} while(--i_time);
			
			printf("avg result = %.2f\n", total * 1.0 / times_main);
			
			break;
		case CMD_TRY:
			for(int i_d = 1; i_d <= max_d_main; i_d++) {
				for(int i_rc = 2; i_rc < (2 * i_d + 1) * (2 * i_d + 1); i_rc++) {
					int state[COL][ROW] = {{0}};
					int temp[COL][ROW] = {{0}};
					int logs[ROUND][COL][ROW] = {{{0}}};
					int idx = 0;
					
					printf("d = %d, rc = %d", i_d, i_rc);

					init_screen();
					
					init_state(state, COL, ROW);
					
					iter = max_iter_main;
					
					do {
						print_screen(max_iter_main - iter + 1, state);
						makenext_move(state, temp, COL, ROW, i_d, i_rc);
						
						if (check_dup_all(logs, state, COL, ROW, ROUND)) break;
						
						log_result(logs[idx], state, COL, ROW);
						
						idx = (idx + 1) % ROUND;
					} while(--iter);
					
					result = calc_result(state, COL, ROW);
					
					printf(", result = %d (stopped at iter %d)\n", result, max_iter_main - iter);
					
					cleanup_screen();
				}
			}
			break;
		case CMD_SET:			
			i_time = times_main;
			
			total = 0;
			
			do {
				int state[COL][ROW] = {{0}};
				int temp[COL][ROW] = {{0}};
				int logs[ROUND][COL][ROW] = {{{0}}};
				int idx = 0;
				
				printf("#%d ", times_main - i_time + 1);

				init_screen();
				
				init_state(state, COL, ROW);
				
				iter = max_iter_main;
				
				do {
					print_screen(max_iter_main - iter + 1, state);
					makenext_move(state, temp, COL, ROW, set_d_main, set_rational_count_main);
					
					if (check_dup_all(logs, state, COL, ROW, ROUND)) break;
					
					log_result(logs[idx], state, COL, ROW);
					
					idx = (idx + 1) % ROUND;
				} while(--iter);
				
				result = calc_result(state, COL, ROW);
				total += result;
				
				printf("result = %d (stopped at iter %d)\n", result, max_iter_main - iter);
				
				cleanup_screen();
			} while(--i_time);
			
			printf("avg result = %.2f\n", total * 1.0 / times_main);
			
			break;
	}	

	return 0;
}
