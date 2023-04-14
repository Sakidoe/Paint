#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "init.h"

void get_rules(int argc, char * argv[], int* rows, int* cols){
    if (argc == 1) {
        *rows = 10;
        *cols = 10;
        //printf("%d", *rows);
    } else if(argc == 3) {
        *rows = atoi(argv[1]);
        *cols = atoi(argv[2]);
       // printf("%d", *rows);
    } else {
        printf("you suck");
        exit(0);
    }

    
}
void create_board(item* board) {
    board->the_board = (char**)malloc(board->num_rows* sizeof(char*));
    for(int i = 0; i < board->num_rows; ++i){
        board->the_board[i] = (char*)malloc(board->num_cols * sizeof(char));
        for(int j = 0; j < board->num_cols; ++j){
            board->the_board[i][j] = '*';
        }
    }
}

void display_board(item* board) { 
    int i, j;
   //int l = board.num->rows-1;
    for(i = 0; i < board->num_rows; ++i){
        printf("%d ", board->num_rows-i-1);
        for(j = 0; j < board->num_cols; ++j) {
            printf("%c ", board->the_board[i][j]);
        }
        printf("\n");
        //l--;
    }
    printf("  ");
    for (int v = 0; v < board->num_cols; v++) {
		printf("%d ", v);
	}
	printf("\n");
}

void clean_up(item *board){
    
    for(int i = 0; i < board->num_rows; ++i){
        free(board->the_board[i]);
		board->the_board[i] = NULL;
	}
	free(*(board->the_board));
	*(board->the_board) = NULL;
	board = NULL;
}

/*
void get_command(Command* command){
	char input[30];
	char *c = NULL;
	char str[] = "qhweradsl";
	
	while (true)
	{
		printf("Enter your command: ");
		fgets(input, sizeof(input), stdin);
		c = strtok(input," ");
		
		if ((c != NULL) && (strlen(c) == 2) && c[1]=='\n') {
			if (c[0] == 'q' || c[0] == 'h'){
				command->op_co = c[0];
				break;
			} else {
				printf("Wrong number of command line arguements entered.\n");
				continue;
			}
		}
		//printf("c: %s. strlen(c): %ld.", c, strlen(c));
		
		if ((c == NULL) || (strlen(c) > 1)) {
			printf("Unrecognized command. Type h for help.\n");
			continue;
		} else if (strchr(str, c[0]) == NULL) {
			printf("Unrecognized command.... Type h for help.\n");
			continue;
		} 
		command->op_co = c[0];
		
		
		
		break;
	}
}

void run_command(item *canvas, Command* command){
//printf("command.op_co: %c\n", command->op_co);
	if (command->op_co == 'h')
	{
		print_help();
	}
	
}

void operate(item *canvas){
	
	while(true){
		Command command;
		get_command(&command);
		if (command.op_co == 'q')
		{
			break;
		}
		run_command(canvas, &command);
	}
}*/
