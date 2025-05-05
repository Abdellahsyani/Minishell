/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:36:59 by asyani            #+#    #+#             */
/*   Updated: 2025/04/27 16:03:45 by abdo             ###   ########.fr       */
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

/* struct for gc_collector */
typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	char	*content;
	int	type;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	*tok;
	int	i;
	int	len;
	int	st;
}	t_shell;

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
int	ft_isalpha(char c);
int	is_operator(char op);
char	*ft_strlcpy(char *token, char *input, int len, int j);
int	ft_strcmp(char *s1, char *s2);
char	*token_type(t_token *list);

#endif
