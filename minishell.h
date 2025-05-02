/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:36:59 by asyani            #+#    #+#             */
/*   Updated: 2025/05/02 09:24:11 by abhimi           ###   ########.fr       */
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
# include <limits.h>

enum e_type
{
    redir_output, // >
    redir_input, // <
    d_herdoc, // <<
    redir_o_app, // >>
    word,
    pipe,
};

typedef struct s_env
{
    char    *key;
    char    *value;
    struct t_env *next;
} t_env;


int     ft_strcmp(char *s1, char *s2);
void    ft_echo(char **arg);
int     cd(char **args, s_env *env);
void    ft_pwd(char **args);
void    ft_env(s_env *env);
int     is_valid(char *str)

#endif
