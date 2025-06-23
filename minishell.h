/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:36:59 by asyani            #+#    #+#             */
/*   Updated: 2025/06/22 18:58:11 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "gc.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

/*** struct for tokinization ***/
typedef struct s_shell
{
	char				*tok;
	int					i;
	int					len;
	int					st;
}						t_shell;

typedef struct s_token
{
	char				*content;
	int					type;
	struct s_token		*next;
}						t_token;

/**struct to hold all double quote variable*/
typedef struct s_hold
{
	int					i;
	char				*var;
	int					count;
	char				*exp;
	char				*get_v;
	char				*var1;
	int					len;
	int					len1;
	char				**env;
	char				**env_var;
	int					coun;
	int					*track_size;
	int					*track_s;
	int					counts;
	int					j;
	int					k;
	int					size_all;
}						t_hold;

/*** enum struct for get type of tokens ****/
typedef enum e_type
{
	redir_output,
	redir_input,
	d_herdoc,
	redir_o_app,
	word,
	pipe_line
}						t_token_type;

/**** struct for execution ***/
typedef struct s_env
{
	char				*key;
	char				*value;
	int					flag;
	struct s_env		*next;
}						t_env;

/** struct for redir**/
typedef struct s_redi
{
	char				*file;
	t_token_type		type;
	struct s_redi		*next;
}						t_redi;

typedef struct s_command
{
	char				**argv_t;
	char				**argv;
	int					fd;
	t_redi				*in;
	t_redi				*out;
	struct s_command	*next;
}						t_command;

typedef struct s_extra
{
	int					i;
	int					size;
	int					flag_sig;
	pid_t				*pid;
	int					**pipline;
	t_env				**env;
	char				**envp;
	struct s_extra		*next;
}						t_extra;

/** expand functions **/
void					expand_var(t_command *cmd, t_env **env);
char					*double_quote(char *str, t_env **env);
char					*get_var(char *str, t_env **env, int i);
char					*get_var1(char *str);
char					*single_quote(char *content);
char					*copy_var(char *content, t_env **env, int i);

/***** parsing functions *****/
char					*split_part(t_token **cur, char *content, t_env **env,
							int i);
void					add_to_argv(t_command *cmd, char *str);
void					create_new_node(int count, t_command **cmd,
							t_command **cur);
void					add_lis(t_redi **list, t_redi *new_node);
t_redi					*create_nod(void);
void					pars_command(t_token *list, t_command **cmd_list,
							t_env **env);
int						start_parsing(t_token *list, t_env **env);

/** tokinazation functions **/
t_token					*create_node(char *c);
void					add_list(t_shell *mini, t_token **list);
int						handle_blank(t_shell *mini, t_token **list, char *line);
int						handle_quotes(t_shell *mini, t_token **list,
							char *line);
int						handle_op(t_shell *mini, t_token **list, char *line);
int						create_token(t_shell *mini, t_token **list, char *line);
int						handle_dollar(t_shell *mini, t_token **list,
							char *line);
int						get_input(char *line, t_token **tokens_list);
char					*ft_strlcpy(char *token, char *input, int len, int j);
void					*token_type(t_token *list);

/************** free functions  ******************/
void					clean_all(t_env **env, int n, int flag);
void					free_2d(char **arr);
void					ft_free_env(t_env **p);

/******** helper functions ************/
void					count_space(char *str, char *result, int *i, int *j);
char					*rem_double(char *content);
char					*stcopy(char *var, char *content, char del);
char					*get_status(char *str, t_env **env, int i, int j);
void					failure_alloc(t_command *cmd, char *ex);
char					*ft_strjoins(char *s1, char *s2);
void					add_cmd_list(int count, t_command **cmd);
void					*gc_malloc(size_t size);
int						is_operator(char op);
int						ft_strcmp(char *s1, char *s2);
int						is_valid(char *str);
int						ft_check_value(char *str, t_env *env);
t_env					*ft_find(t_env *env, char *key);
t_env					**get_env(char **list);
int						count_word_tokens(t_token *list);
void					set_new_env(char *key, char *value, t_env **env);
char					**chr_envirment(t_env **env);
void					delete_key_value(char *key, t_env **env);
char					*ft_key(char *str);
void					update_path(char *arg, t_env **env);
char					*ft_get(t_env **env, char *key);
int						ft_cmd_size(t_command **cmd);
char					*rm_newline(char *limit);
int						ft_strccmp(const char *s1, const char *s2, int l);

//**************Builtin****************

int						ft_echo(char **arg);
int						ft_cd(char **args, t_env **env);
int						ft_pwd(t_env **env);
int						ft_env(t_env **env, char **argv);
int						ft_export(char **arg, t_env **env);
int						ft_unset(char **arg, t_env **env);
void					ft_exit(char **arg, int last_status, t_env **env);

//***************Execution**************
void					ft_exec(t_command **cmd, t_env **env);
void					wait_and_free(t_extra ptr);
void					helper_herdoc(char *line, int fd, t_env **env);
int						ft_handle_herdoc(char *value, t_env **env, int *n);
void					write_in_file(int fd, t_env **env, char *limiter);
void					ft_herdoc(t_command **cmd, t_extra *ptr);
int						ft_exec_builtin(char *cmd, char **args, t_env **env);
char					*find_path(char *cmd, t_env **env);
t_env					**get_env(char **list);
int						is_builtin(t_command *cmd);
void					update_exit_status(t_env **env, int status);
int						redirect_handler(int *fd, t_command **cmd, t_env **env);
int						input_handle(t_redi *redir);
int						output_handle(t_redi *redir);
void					closingfds(int **tube, int pos);
int						pass_out(t_redi *tmp, int *fd);
void					handle_sig(int signum);
void					handle_child_sig(int signum);
void					handle_child(t_command *cmd, t_extra ptr);
void					init_extra(t_extra *ptr, t_env **env);
char					*ft_strdup1(const char *s1);
#endif
