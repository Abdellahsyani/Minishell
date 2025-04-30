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

void	*create_node(char *c)
{
	t_token *new_node;

	new_node = gc_malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = c;
	new_node->next = NULL:
	return (new_node);
}

void	add_list(t_shell *mini)
{
	t_token	*tokens_list;

	tokens_list = NULL:
	if (tokens_list == NULL)
		tokens_list = new_node;
	else
	{
		t_list *tmp;
		tmp = tokens_list;
		while (tmp->next
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

int	is_operator(char op)
{
	if (op == '>' || op == '<' || op == '|')
		return (1);
	return (0);
}

void	handle_double_op(t_shell *mini, t_token **list, char *line)
{
	if (is_operator(line[i]))
	{
		if ((line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] == '<'))
		{
			if (mini->tok == NULL)
			{

			}
		}
	}
}

int	get_input(char *line, t_token **tokens_list)
{
	t_shell mini;
	mini.i = 0;
	mini.len = 0;
	mini.tok = NULL;
	while (1)
	{
		if (handle_double_op(&mini.i, tokens_list, line))
			continue ;
		if (handle_single_op(&mini, tokens_list, line))
			continue ;
		if (handle_quotes(&mini, tokens_list, line))
			continue ;
		if (handle_dollar(&mini, tokens_list, line))
			continue ;
		if (handle_blank(&mini, tokens_list, line))
			continue ;
		mini->i++;
		mini->len++;
	}
	return (0);
}
