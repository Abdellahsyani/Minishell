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

t_token	*create_node(char c)
{
	t_token *new_node;

	new_node = gc_malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = c;
	new_node->next = NULL:
	return (new_node);
}

void	add_list(char tok)
{
	t_token	*tokens_list;

	tokens_list = NULL:
	if (tokens_list == NULL)
		tokens_list = new_node;
	else
	{
		t_list *tmp;
		tmp = tokens_list;
		while (tmp->next)
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

void	handle_double_op(t_shell *mini)
{
	if (mini->tokens_list->next == NULL)
	{
		add_list(mini->line[i]);
		mini->new_node->content = '\0';
	}
	else
	{
		mini->tokens_list->content = '\0';
		add_list(mini->line[i]);
	}
}

void	get_input(t_shell *mini)
{
	mini->i = 0;
	while (mini->line[i])
	{
		if (mini->line[i] == '<' && mini->line[i + 1] == '<' || maini->line[i] == '>' && mini->line[i + 1] == '>')
			handle_double_op(mini);
		if (is_operator(mini->line[i]))
			handle_single_op(mini);
		if (mini->line[i] == '"' || mini->line[i] == '\'')
			handle_quotes(mini);
		if (mini->line[i] == '$')
			handle_dollar(mini);
		if (mini->line[i] == ' ')
			handle_blank(mini);
	}
}
