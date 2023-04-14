NAME = paint.out
SRCS = main.c board.c run_command.c commands.c
FLAGS = -Wall -Werror

all:
	gcc $(FLAGS) -o $(NAME) $(SRCS) -I .
	
clean:
	rm -f $(NAME)
