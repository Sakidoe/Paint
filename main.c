#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "init.h"
int main(int argc, char *argv[]){
 
    int row, col;
    item board;
    get_rules(argc, argv, &row, &col);
    board.num_rows = row;
    board.num_cols = col;
    create_board(&board);
    display_board(&board);
    operate(&board);
    clean_up(&board);

    return(0);
}
