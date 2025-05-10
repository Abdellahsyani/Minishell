/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:20:25 by asyani            #+#    #+#             */
/*   Updated: 2025/04/26 13:26:20 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *create_node(char *c)
{
	t_token *new_node;
	new_node = gc_malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = c;
	new_node->next = NULL;
	new_node->type = -1;
	return (new_node);
}

void add_list(t_shell *mini, t_token **list)
{
	t_token *new_node;

	if (!mini->tok)
		return;
	new_node = create_node(mini->tok);
	if (!new_node)
		return;
	if (*list == NULL)
		*list = new_node;
	else
	{
		t_token *tmp;
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

int create_token(t_shell *mini, t_token **list, char *line)
{
	if (mini->len == 0)
		return (0);
	mini->tok = ft_strlcpy(mini->tok, line, mini->len, mini->st);
	if (!mini->tok)
		return (0);
	add_list(mini, list);
	mini->len = 0;
	mini->tok = NULL;
	mini->st = mini->i;
	return (1);
}

int handle_op(t_shell *mini, t_token **list, char *line)
{
	if (!is_operator(line[mini->i]))
		return (0);
	if (mini->len > 0)
		create_token(mini, list, line);
	mini->st = mini->i;
	mini->len = 1;
	if ((line[mini->i] == '>' && line[mini->i + 1] == '>') ||
		(line[mini->i] == '<' && line[mini->i + 1] == '<'))
		mini->len = 2;
	if (mini->len == 2)
		mini->i++;
	create_token(mini, list, line);
	mini->i++;
	mini->st = mini->i;
	return (1);
}

int handle_quotes(t_shell *mini, t_token **list, char *line)
{
	char	quote_type;
	int	start_i;

	if (line[mini->i] != '"' && line[mini->i] != '\'')
		return (0);
	quote_type = line[mini->i];
	start_i = mini->i + 1;
	mini->i++;
	while (line[mini->i] && line[mini->i] != quote_type)
		mini->i++;
	mini->len += (mini->i) - start_i;
	mini->st = start_i;
	if (line[mini->i] == quote_type)
		mini->i++;
	return (1);
}

int handle_blank(t_shell *mini, t_token **list, char *line)
{
	if (line[mini->i] != ' ' && line[mini->i] != '\t')
		return (0);
	if (mini->len > 0)
		create_token(mini, list, line);
	while (line[mini->i] == ' ' || line[mini->i] == '\t')
		mini->i++;
	mini->st = mini->i;
	return (1);
}

int handle_dollar(t_shell *mini, t_token **list, char *line)
{
	int	start_d;

	if (line[mini->i] != '$')
		return (0);
	if (mini->len > 0)
		create_token(mini, list, line);
	start_d = mini->i;
	mini->i++;
	while ((ft_isalpha(line[mini->i]) != 0) || line[mini->i] == '_')
		mini->i++;
	mini->len += mini->i - start_d;
	return (1);
}

int get_input(char *line, t_token **tokens_list)
{
	t_shell mini;

	mini.i = 0;
	mini.st = 0;
	mini.len = 0;
	mini.tok = NULL;

	while (line[mini.i] != '\0')
	{
		if (handle_op(&mini, tokens_list, line))
			continue;
		if (handle_quotes(&mini, tokens_list, line))
			continue;
		if (handle_blank(&mini, tokens_list, line))
			continue;
		if (handle_dollar(&mini, tokens_list, line))
			continue;
		mini.i++;
		mini.len++;
	}
	if (mini.len > 0)
		create_token(&mini, tokens_list, line);
	return (0);
}
