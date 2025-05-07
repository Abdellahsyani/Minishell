NAME=minishell

CC=cc

CFLAG= -Wall -Werror -Wextra
RM= rm -rf 
SRC=

OBJ=${SRC:.c=.o}

all:$(NAME)


clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean all
	
