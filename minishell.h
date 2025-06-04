/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:36:59 by asyani            #+#    #+#             */
/*   Updated: 2025/06/04 11:56:37 by abhimi           ###   ########.fr       */
/*   Updated: 2025/06/04 11:37:01 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "gc.h"

/*** struct for tokinization ***/
typedef struct s_shell
{
	char	*tok;
	int	i;
	int	len;
	int	st;
}	t_shell;

typedef struct s_token
{
	char	*content;
	int	type;
	struct s_token	*next;
}	t_token;

/*** enum struct for get type of tokens ****/
typedef enum e_type
{
    redir_output, // >
    redir_input, // <
    d_herdoc, // <<
    redir_o_app, // >>
    word,
    pipe_line
} t_token_type;

/**** struct for execution ***/
typedef struct s_env
{
    char    *key;
    char    *value;
    pid_t     pid;
    int     flag;
    struct s_env *next;
} t_env;

/** struct for redir**/
typedef struct s_redi
{
    char *file;
    t_token_type type;
    struct s_redi *next;
}	t_redi;

typedef struct s_command
{
    char	**argv_t;
    char	**argv;
    int		fd;
    t_redi	*in;
    t_redi	*out;
    struct s_command *next;
} t_command;

typedef struct s_extra
{
    int i;
    int size;
    pid_t *pid;
    int **pipline;
    t_env **env;
    char **envp;
    struct s_extra *next;
} t_extra;

/*test*/
int	pars_command(t_token *list, t_command **cmd_list);

/** expand functions **/
void	expand_var(t_command *cmd, t_env **env);
char	*double_quote(char *str, t_env **env);
char	*get_var(char *str, t_env **env);
char	*get_var1(char *str);

/***** parsing functions *****/
t_token	*create_node(char *c);
void	add_list(t_shell *mini, t_token **list);
int	handle_blank(t_shell *mini, t_token **list, char *line);
int	handle_quotes(t_shell *mini, t_token **list, char *line);
int	handle_op(t_shell *mini, t_token **list, char *line);
int	create_token(t_shell *mini, t_token **list, char *line);
int	handle_dollar(t_shell *mini, t_token **list, char *line);
int	get_input(char *line, t_token **tokens_list);
char	*ft_strlcpy(char *token, char *input, int len, int j);
void	*token_type(t_token *list);
int	start_parsing(t_token *list, t_env **env);

/******** helper functions ************/
void	free_2d(char **arr);
void	add_cmd_list(t_token *list, t_command **cmd);
void	*gc_malloc(size_t size);
int	is_operator(char op);
int     ft_strcmp(char *s1, char *s2);
int     is_valid(char *str);
int     ft_check_value(char *str, t_env *env);
t_env   *ft_find(t_env *env, char *key);
t_env   **get_env(char **list);
int	count_word_tokens(t_token *list);
void    set_new_env(char *key, char *value, t_env **env);
char    **chr_envirment(t_env **env);
void    delete_key_value(char *key, t_env **env);
char    *ft_key(char *str);
void    update_path(char *arg, t_env **env);
char    *ft_get(t_env **env, char *key);
int     ft_cmd_size(t_command **cmd);

//**************Builtin****************

int    ft_echo(char **arg);
int     ft_cd(char **args, t_env **env);
int    ft_pwd(char **args, t_env **env);
int     ft_env(t_env **env, char **argv);
int     ft_export(char **arg, t_env **env);
int     ft_unset(char **arg, t_env **env);
int     ft_exit(char **arg,int last_status);

//***************Execution**************
void ft_exec(t_command **cmd, t_env **env);
void	wait_and_free(t_extra ptr);
void	helper_herdoc(char *line, int fd, t_env **env);
int	ft_handle_herdoc(char *value, t_env **env);
void    write_in_file(int fd, t_env **env, char *limiter);
void    ft_herdoc(t_command **cmd,t_env **env);
int     ft_exec_builtin(char *cmd, char **args, t_env **env);
char    *find_path(char *cmd, t_env **env);
t_env   **get_env(char **list);
int     is_builtin(t_command *cmd);
void    update_exit_status(t_env **env,int status);
int     redirect_handler(int *fd, t_command **cmd , t_env **env);
int     input_handle(t_redi *redir);
int     output_handle(t_redi *redir);
void    closingfds(int **tube, int pos);
int     pass_out(t_redi *tmp ,int *fd);
void    handle_sig(int signum);
void    handle_child_sig(int signum);
void    handle_child(t_command *cmd, t_extra ptr);

#endif
