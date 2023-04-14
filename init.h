#include <stdio.h>
#ifndef INIT_H
#define INIT_H
typedef struct board_item
{
  char** the_board;
  int num_rows;
  int num_cols;
}item;
typedef struct Comm
{
    char op_co;
    char op_to;
    int op_at;
    char* filename;
    int row1,col1,row2,col2;
}Command;
  //FILE* validate_input(int argc, char* argv[]);
    bool isNumber(char number[]);
    void get_rules(int argc, char * argv[], int* rows, int* cols);
    void create_board(item* board);
    void display_board(item * board);
    void clean_up(item *board);
    void run_command(item *board, Command* command);
    void get_command(item* board,Command* command);
    void operate(item *board);
    void print_help();
    void delete_matrix(char*** board, int row_dim, int col_dim);
    void write_board(item* board, Command* command);
    void erase_board(item* board, Command* command);
    void add(item *board, Command* command);
	void delete(item *board, Command* command);
    void save(item *board, Command* command);
    void load(item *board, Command* command);
#endif
