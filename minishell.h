/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:36:59 by asyani            #+#    #+#             */
/*   Updated: 2025/05/23 17:42:04 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

/* struct for gc_collector */
// typedef struct s_list
// {
// 	void			*data;
// 	struct s_list	*next;
// }	t_list;

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

typedef enum e_type
{
    redir_output, // >
    redir_input, // <
    d_herdoc, // <<
    redir_o_app, // >>
    word,
    pipe_line
} t_token_type;

void	ft_free_gc(void);
void	*gc_malloc(size_t size);
// char	*ft_strdup(char *s1);

t_token	*create_node(char *c);
void	add_list(t_shell *mini, t_token **list);
int	handle_blank(t_shell *mini, t_token **list, char *line);
int	handle_quotes(t_shell *mini, t_token **list, char *line);
int	handle_op(t_shell *mini, t_token **list, char *line);
int	create_token(t_shell *mini, t_token **list, char *line);
int	handle_dollar(t_shell *mini, t_token **list, char *line);
int	get_input(char *line, t_token **tokens_list);
int	is_operator(char op);
char	*ft_strlcp(char *token, char *input, int len, int j);
int	ft_strcmp(char *s1, char *s2);
char	*token_type(t_token *list);
int	start_parsing(t_token *list);

typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env *next;
} t_env;


typedef struct s_redi
{
    char *file;
    t_token_type type;
    struct s_redi *next;
}t_redi; 

typedef struct s_command
{
    char **arg;
    t_env **env;
    int fd;
    t_redi *in;
    t_redi *out;
    // t_token_type type;
    struct s_command *next;
} t_command;


typedef struct s_extra
{
    int i;
    int size;
    pid_t *pid;
    int **pipline;
    t_env **env;
    struct s_extra *next;
} t_extra;

int     ft_strcmp(char *s1, char *s2);
int     is_valid(char *str);
t_env   *ft_find(t_env *env, char *key);
t_env   **get_env(char **list);
void    set_new_env(char *key, char *value, t_env **env);
char    **chr_envirment(t_env **env);

//**************Builtin****************

int    ft_echo(char **arg);
int     ft_cd(char **args, t_env *env);
int    ft_pwd(char **args);
int     ft_env(t_env **env);
int     ft_export(char **arg, t_env **env);
int     ft_unset(char **arg, t_env **env);
int     ft_exit(char **arg,int last_status);

//***************Execution**************
int     ft_exec_builtin(char *cmd, char **args, t_env **env);
char    *find_path(char *cmd, t_env **env);
t_env   **get_env(char **list);
int     is_builtin(t_command *cmd);
void    update_exit_status(t_env **env,int status);
int     redirect_handler(int fd, t_command **cmd , t_env **env);
int     input_handle(t_redi *redir);
int     output_handle(t_redi *redir);
void    closingfds(int **tube, int pos);

#endif
