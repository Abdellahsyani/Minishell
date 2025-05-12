/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:36:59 by asyani            #+#    #+#             */
/*   Updated: 2025/05/10 14:48:43 by abhimi           ###   ########.fr       */
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
char	*ft_strdup(const char *s1);

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


typedef struct s_command
{
    char *name;
    char **arg;
    t_env **env;
    char   *status;
} t_command;

typedef struct s_redi
{
    char *file;
    t_token_type redir;
    struct s_redi *next;
}t_redi;


int     ft_strcmp(char *s1, char *s2);
int     is_valid(char *str);
t_env   *find(t_env *env, char *key);
t_env   **get_env(char **list);
// int ft_strncmp(char *s1, char *s2, int l);

//**************Builtin****************

int    ft_echo(char **arg);
int     cd(char **args, t_env *env);
int    ft_pwd(char **args);
int    ft_env(t_env **env);
int     ft_export(char **arg, t_env **env);
int     ft_unset(char **arg, t_env *env);
int     ft_exit(char **arg,int last_status);

//***************Execution**************
int     exec_builtin(char *cmd, char **args, char **envp);
char    *find_path(char *cmd, t_env **env);
t_env   **get_env(char **list);
int     simple_cmd(t_command *cmd);
int     exec_builtin(char *cmd, char **args, char **envp);

#endif
