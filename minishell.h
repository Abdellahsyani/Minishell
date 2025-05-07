/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:36:59 by asyani            #+#    #+#             */
/*   Updated: 2025/05/06 15:10:59 by abhimi           ###   ########.fr       */
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

enum e_type
{
    redir_output, // >
    redir_input, // <
    d_herdoc, // <<
    redir_o_app, // >>
    word,
    pipe_line,
};

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
} t_command;

int     ft_strcmp(char *s1, char *s2);
int     is_valid(char *str);
t_env   *find(t_env *env, char *key);
t_env   **get_env(char **list);
int ft_strncmp(char *s1, char *s2, int l);

//**************Builtin****************

int    ft_echo(char **arg);
int     cd(char **args, t_env *env);
int    ft_pwd(char **args);
int    ft_env(t_env **env);
int     ft_export(char **arg, t_env **env);
int     ft_unset(char **arg, t_env *env);
int     ft_exit(char **arg,int last_status);

//***************Execution**************
int exec_builtin(char *cmd, char **args, char **envp);

#endif
