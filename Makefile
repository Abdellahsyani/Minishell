NAME=minishell

CC=cc
MAKE= make
CFLAG= -Wall -Werror -Wextra
RM= rm -rf 
SRC= main.c gc_collector.c tokinazer/start_token.c tokinazer/token_type.c tokinazer/utils.c parsing/expand.c parsing/pars.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c \
	builtin/pwd.c builtin/unset.c execution/exec_builtin.c execution/exec_dir.c execution/exec.c execution/find_path.c execution/ft_herdoc.c execution/ft_herdoc2.c execution/get_env.c \
	execution/update_exit_st.c
LIBFT = ./libft
OBJ=${SRC:.c=.o}

all:$(NAME)

$(NAME) : $(OBJ)
		$(MAKE) -C $(LIBFT)
		$(CC) $(CFLAG) $(OBJ) ./libft/libft.a -o $(NAME) -lreadline

%.o: %.c 
	$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean all
	
