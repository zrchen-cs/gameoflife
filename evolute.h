int init_state(int current[COL][ROW], int col, int row);

int calc_result(int current[COL][ROW], int col, int row);

void log_result(int target[COL][ROW], int current[COL][ROW], int col, int row);

int check_dup_all(int logs[ROUND][COL][ROW], int current[COL][ROW], int col, int row, int round);

void makenext(int a[COL][ROW], int b[COL][ROW], int col, int row);

void makenext_move(int a[COL][ROW], int b[COL][ROW], int col, int row, int set_d_main, int set_rational_count_main);
