#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "init.h"

void write_board(item* board, Command* command) {
    if(command->row1 == command->row2){
		    if(command->col1 < command->col2){
		    for(int a = command->col1; a < (command->col2)+1; a++){
		        if(board->the_board[(-(command->row1 - board->num_rows))-1][a] == '*') {
		            board->the_board[(-(command->row1 - board->num_rows))-1][a] = '-';
		        } else { 
		            board->the_board[(-(command->row1 - board->num_rows))-1][a] = '+';
		        }
		    }
		    }
		    if(command->col1 > command->col2) {
		        for(int c = command->col2; c < (command->col1)+1; c++){
		        if(board->the_board[(-(command->row1 - board->num_rows))-1][c] == '*') {
		            board->the_board[(-(command->row1 - board->num_rows))-1][c] = '-';
		        } else { 
		            board->the_board[(-(command->row1 - board->num_rows))-1][c] = '+';
		        }
		    }
		    
		}
		display_board(board);
	    } else if (command->col1 == command->col2) {
	        if( command->row2 > command->row1) {
	        for(int b = command ->row1; b < (command->row2)+1; b++) {
	            if(board->the_board[b][command->col1] == '*') {
		            board->the_board[b][command->col2] = '|';
		        } else {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		            board->the_board[b][command->col1] = '+';
		        }
	        }
	        }
	        if(command->row1 > command-> row2) { 
	            for(int bb = command ->row2; bb < (command->row1)+1; bb++) {
	            if(board->the_board[bb][command->col1] == '*') {
		            board->the_board[bb][command->col2] = '|';
		        } else { 
		            board->the_board[bb][command->col1] = '+';
		        }
	        }
	        }
	        display_board(board);
	    } else if((command->row1 - command->col1) == (command->row2 - command->col2)){
	        if(command->row1 < command->row2){
	        int e= command->col1;
	        for(int d = (command->row1)+1;d < (command->row2)+2;d++) {
	            	if( board->the_board[-(d - board->num_rows)][e] == '*'){
	                board->the_board[-(d - board->num_rows)][e] = '/';
	                e++;
			} else {
			board->the_board[-(d - board->num_rows)][e] = '+';
	                e++;
			}
	        }
	        }
	        if (command->row2 < command->row1) {
	            int f = command->col2;
	            for(int ff = (command->row2)+1;ff < (command->row1)+2;ff++) {
	            	if( board->the_board[-(ff - board->num_rows)][f] == '*'){
	                board->the_board[-(ff - board->num_rows)][f] = '/';
	                f++;
			} else {
			board->the_board[-(ff - board->num_rows)][f] = '+';
	                f++;
			}
	        }
	        }
	        display_board(board);
	        
	    } else if((command->row1 + command->col1) == (command->row2 + command->col2)){
	        if(command->row1 > command->row2){
	        int h= command->col2;
	        for(int gg = (command->row2)+1;gg < (command->row1)+2;gg++) {
	            	if( board->the_board[(-(gg - board->num_rows))][h] == '*'){
	                board->the_board[(-(gg - board->num_rows))][h] = '\\';
	                h--;
			} else {
			        board->the_board[(-(gg - board->num_rows))][h] = '+';
	                h--;
			}
	        }
	        }
	        if(command->row2 >command->row1){
	            int i = command->col1;
	             for(int hh = (command->row1)+1;hh < (command->row2)+2;hh++) {
	            	if( board->the_board[(-(hh - board->num_rows))][i] == '*'){
	                board->the_board[(-(hh - board->num_rows))][i] = '\\';
	                i--;
			} else {
			        board->the_board[(-(hh - board->num_rows))][i] = '+';
	                i--;
			}
	        }
	        }
	        display_board(board);
	    }
}