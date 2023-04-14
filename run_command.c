#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "init.h"
char** make_empty_matrix(int row_dim, int col_dim) {

	char **ary; //declare the array pointer
	ary = (char **) malloc(sizeof(char *)*row_dim);
    for(int i = 0; i < row_dim; i++)
    {
        ary[i] = (char *) malloc(sizeof(char)*col_dim);
    }
    if (ary == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else {
		return ary;
	}
}

void add(item* board, Command* command) {
    if (command->op_to == 'r') {
		char** matrix = (char**)malloc(board->num_rows * sizeof(char*));
		for(int i = 0; i < board->num_rows; ++i){
			matrix[i] = (char*)malloc(board->num_cols * sizeof(char));
			for(int j = 0; j < board->num_cols; ++j){
				matrix[i][j] = board->the_board[i][j];
			}
		}
		delete_matrix(&board->the_board, board->num_rows, board->num_cols);
		board->the_board = make_empty_matrix(board->num_rows+1, board->num_cols);
		
		for(int i = 0; i < board->num_rows+1; ++i){
			for(int j = 0; j < board->num_cols; ++j) {
				if (i < command->op_at) {
					board->the_board[i][j] = matrix[i][j];
				} else if (i == command->op_at) {
				    board->the_board[i][j] = '*';
				} else if (i > command->op_at) {
					board->the_board[i][j] = matrix[i-1][j];
				}
			}
		}
		for(int i = 0; i < board->num_rows-1; ++i){
			free(matrix[i]);
			matrix[i] = NULL;
		}
		free(*(matrix));
		*(matrix) = NULL;
		board->num_rows = board->num_rows + 1;
		
	}

	if (command->op_to == 'c') {
		for(int i = 0; i < board->num_rows; ++i){
			char line[board->num_cols];
			strcpy(line, board->the_board[i]);
			free(board->the_board[i]);
			board->the_board[i] = NULL;
			board->the_board[i] = (char*)malloc(board->num_cols+1 * sizeof(char));
			for (int j = 0; j < board->num_cols+1; ++j) {
				if (j < command->op_at) {
					board->the_board[i][j] = line[j];
				} else if (j == command->op_at) {
					board->the_board[i][j] = '*';
				} else if (j > command->op_at) {
					board->the_board[i][j] = line[j-1];
				}
			}
		}
	board->num_cols = board->num_cols + 1;
	}
    display_board(board);
}

void delete(item *board, Command* command){
	if (command->op_to == 'r') {
		for(int i = command->op_at; i < board->num_rows-1; i++){
			for (int j = 0; j < board->num_cols; j++) {
				board->the_board[i][j] = board->the_board[i+1][j];
			}
		}
		free(board->the_board[board->num_rows-1]);
		board->the_board[board->num_rows-1] = NULL;	
		
		board->num_rows =board->num_rows - 1;
	}

	if (command->op_to == 'c') {
		for(int i = 0; i < board->num_rows; ++i){
			char line[board->num_cols];
			strcpy(line,board->the_board[i]);
			free(board->the_board[i]);
			board->the_board[i] = NULL;
			board->the_board[i] = (char*)malloc(board->num_cols-1 * sizeof(char));
			int k=0;
			for (int j = 0; j < board->num_cols-1; ++j) {
				if (j != command->op_at) {
				    board->the_board[i][k] = line[j];
					k++;
				}
			}
		}
		board->num_cols = board->num_cols - 1;
	}
    display_board(board);
}
void delete_matrix(char*** board, int row_dim, int col_dim) {

    for (int i = 0; i < row_dim; i++) {
		free((*board)[i]);
		(*board)[i] = NULL;
    }
	free(*board);
	*board = NULL;
}
void save(item* board, Command* command){
FILE *pf;
	if((pf = fopen(command->filename, "wb")) == NULL) {
		printf("Improper save command or file could not be created.\n");
		exit(0);
	}
	
	if(fwrite(&(board->num_rows), sizeof(int), 1,pf) != 1) {
		printf("Error");
		exit(0);
	}
	
	if(fwrite(&(board->num_cols), sizeof(int), 1,pf) != 1) {
		printf("Error");
		exit(0);
	}
	
	if(fwrite(*board->the_board, sizeof(char), board->num_rows*board->num_cols, pf) != board->num_rows*board->num_cols) {
		printf("Error");
		exit(0);
	}	
	
	fclose(pf); 
}


void load(item* board, Command* command){
FILE *pf;
	if((pf = fopen(command->filename, "rb")) == NULL) {
		printf("Improper load command or file could not be opened.\n");
		exit(0);
	}
	
	//clean up current matrix
    for(int i = 0; i < board->num_rows; ++i){
        free(board->the_board[i]);
		board->the_board[i] = NULL;
	}
	free(*(board->the_board));
	*(board->the_board) = NULL;
	
	//get new rows and cols
	if(fread(&board->num_rows, sizeof(int), 1,pf) != 1) {
		printf("Error reading");
		exit(0);
	}
	
	if(fread(&board->num_cols, sizeof(int), 1,pf) != 1) {
		printf("Error reading");
		exit(0);
	}

   board->the_board = (char**)malloc(board->num_rows * sizeof(char*));
    for(int i = 0; i < board->num_rows; ++i){
        board->the_board[i] = (char*)malloc(board->num_cols * sizeof(char));
	}

	if(fread(*board->the_board, sizeof(char), board->num_rows*board->num_cols, pf) != board->num_rows*board->num_cols) {
		printf("Error writing");
		exit(0);
	}	
	
	fclose(pf); 
	}
	
	
void print_help(){

  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

void operate(item *board){
	
	while(true){
		Command command;
		get_command(board,&command);
		if (command.op_co == 'q')
		{
			break;	
		}
		run_command(board, &command);
		
	}
}

void run_command(item *board, Command* command) { 
    
	if (command->op_co == 'h')
	{
		print_help();
		return;
	}
	
	if (command->op_co == 'w')
	{
		write_board(board, command);
		return;
	}
	if (command->op_co == 'e')
	{
		 board->the_board[command->row1][command->col1] = '*';
	}
	
	if (command->op_co == 'r')
	{
	    if((command->row1 >0)||(command->col1>0)){
		board->num_rows = command->row1;
		board->num_cols = command->col1;
		display_board(board);
		}
		return;
		
	}
	
	if (command->op_co == 'a')
	{
	    add(board, command);

	}
	
	if (command->op_co == 'd')
	{
		delete(board, command);
	}
	if (command->op_co == 's')
	{
		save(board, command);

		
	}
	
	if (command->op_co == 'l')
	{
		load(board,command);
	}
	

}
	


void get_command(item* board, Command* command){
	char input[30];
	char input_copy[30];
	char *c = NULL;
	char str[] = "qhweradsl";
	
	while (true)
	{
		printf("Enter your command: ");
		fgets(input, sizeof(input), stdin);
		strcpy(input_copy, input);
		c = strtok(input," ");

		if ((c != NULL) && (strlen(c) == 2)&& c[1]=='\n') {
			if (c[0] == 'q' || c[0] == 'h'){
				command->op_co = c[0];
				break;
		
			} else if(strchr(str, c[0]) != NULL){
				printf("Wrong number of command line arguements entered.\n");
				continue;
			}
		}
		
		if ((c == NULL) || (strlen(c) > 1)) {
			printf("Unrecognized command. Type h for help.\n");
			continue;
		} else if (strchr(str, c[0]) == NULL) {
			printf("Unrecognized command.... Type h for help.\n");
			continue;
		} 
		int res;
		if (c[0] == 'w') {
			int start_row, start_column, end_row, end_column;
			char oper;
			res = sscanf(input_copy, "%c %d %d %d %d", &oper, &start_row, &start_column, &end_row, &end_column);
			if (res < 5) {
				printf("Wrong number of command line arguements entered.\n");
				continue;				
			} else if (start_row < 0 || start_column < 0 || end_row < 0 || end_column < 0 || start_row > (board->num_rows)-1 || start_column > (board->num_cols)-1 || end_row > (board->num_rows)-1 || end_column > (board->num_cols)-1) {
				printf("row or column number is wrong.\n");
				continue;				
			}
			command->op_co = c[0];
			command->row1 = start_row;
			command->col1 = start_column;
			command->row2 = end_row;
			command->col2 = end_column;
			break;
		}
		
		if (c[0] == 'e') {
			int row, col;
			char oper;
			res = sscanf(input_copy, "%c %d %d", &oper, &row, &col);
			if (res < 3) {
				printf("Wrong number of command line arguements entered.\n");
				continue;				
			} else if (row < 0 || col < 0 || row > board->num_rows || col > board->num_cols ) {
				printf("Improper draw command.\n");
				continue;		
			}
			command->op_co = c[0];
			command->row1 = row;
			command->col1 = col;
			break;
		}
		
		if (c[0] == 'r') {
			int num_rows, num_cols;
			char oper;
			res = sscanf(input_copy, "%c %d %d", &oper, &num_rows, &num_cols);
			if (res < 3) {
				printf("Wrong number of command line arguements entered.\n");
				continue;				
			} else if (num_rows < 1 || num_cols < 1 ) {
				printf("num_rows or num_cols number is wrong.\n");
				continue;		
			}
			command->op_co = c[0];
			command->row1 = num_rows;
			command->col1 = num_cols;
			break;
		}
		
		if (c[0] == 'a') {
			char oper;
			char op_to;
			int op_at;
			res = sscanf(input_copy, "%c %c %d", &oper, &op_to, &op_at);
			if (res < 3) {
				printf("Wrong number of command line arguements entered.\n");
				continue;				
			} else if (op_to != 'r' && op_to != 'c' ) {
				printf("please use 'a [r | c] position' format.\n");
				continue;		
			} else if (op_at < 0  || (op_to == 'r' &&  op_at > board->num_rows) || (op_to == 'c' &&  op_at > board->num_cols) ) {
				printf("Wrong position number entered.\n");
				continue;		
			}
			command->op_co = c[0];
			command->op_to = op_to;
			command->op_at = op_at;
			break;
		}
		
		if (c[0] == 'd') {
			char oper;
			char op_to;
			int op_at;
			res = sscanf(input_copy, "%c %c %d", &oper, &op_to, &op_at);
			if (res < 3) {
				printf("Wrong number of command line arguements entered.\n");
				continue;				
			} else if (op_to != 'r' && op_to != 'c' ) {
				printf("please use 'a [r | c] position' format.\n");
				continue;		
			} else if (op_at < 0  || (op_to == 'r' &&  op_at > board->num_rows) || (op_to == 'c' &&  op_at > board->num_cols) ) {
				printf("Wrong position number entered.\n");
				continue;		
			}
			command->op_co = c[0];
			command->op_to = op_to;
			command->op_at = op_at;
			break;
		}
		
		if (c[0] == 's') {
			char oper;
			char file_name[30];
			res = sscanf(input_copy, "%c %s", &oper, file_name);
			if (res < 2) {
				printf("Wrong number of command line arguements entered.\n");
				continue;				
			} 
			//Removing trailing newline character from file_name
			file_name[strcspn(file_name, "\n")] = 0;
			
			command->op_co = c[0];
			strcpy( command->filename, file_name );
			break;
		}
		
		if (c[0] == 'l') {
			char oper;
			char file_name[30];
			res = sscanf(input_copy, "%c %s", &oper, file_name);
			if (res < 2) {
				printf("Wrong number of command line arguements entered.\n");
				continue;				
			} 
			//Removing trailing newline character from file_name
			file_name[strcspn(file_name, "\n")] = 0;
			
			command->op_co = c[0];
			strcpy( command->filename, file_name );
			break;
		}
		
		
		
		
	}
}