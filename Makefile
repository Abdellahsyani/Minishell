NAME=minishell

CC=cc
MAKE= make
CFLAG= -Wall -Werror -Wextra -g
RM= rm -rf 
SRC= main.c gc_collector.c rem_free.c tokinazer/start_token.c tokinazer/token_type.c tokinazer/utils.c parsing/exp_utils2.c parsing/exp_utils1.c parsing/exp_utils3.c parsing/ex_utils.c parsing/pars_utils1.c parsing/expand.c parsing/pars.c parsing/pars_utils2.c parsing/pr_utils.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c \
	builtin/pwd.c builtin/unset.c execution/exec_builtin.c execution/exec_dir.c execution/exec.c execution/find_path.c execution/ft_herdoc.c execution/ft_herdoc2.c execution/get_env.c \
	execution/update_exit_st.c execution/update_path.c execution/sig.c execution/handle_child.c
LIBFT = ./libft
OBJ=${SRC:.c=.o}

all:$(NAME)

$(NAME) : $(OBJ)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAG) $(OBJ) -g ./libft/libft.a -o $(NAME) -lreadline

%.o: %.c 
	$(CC) $(CFLAG) -c $< -o $@

clean:
	make clean -C ./libft
	$(RM) $(OBJ)
fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean all
