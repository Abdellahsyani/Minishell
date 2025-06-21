/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:04:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/07 10:19:16 by abhimi           ###   ########.fr       */
/*   Created: 2025/04/29 14:51:44 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/06 13:50:58 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_token(t_shell *mini, t_token **list, char *line)
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

t_token	*create_node(char *c)
{
	t_token	*new_node;

	new_node = gc_malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = c;
	new_node->next = NULL;
	new_node->type = -1;
	return (new_node);
}

void	add_list(t_shell *mini, t_token **list)
{
	t_token	*new_node;
	t_token	*tmp;

	if (!mini->tok)
		return ;
	new_node = create_node(mini->tok);
	if (!new_node)
		return ;
	if (*list == NULL)
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	*token_type(t_token *list)
{
	if (!list->content)
		return (NULL);
	while (list)
	{
		if (!ft_strcmp(list->content, ">"))
			list->type = redir_output;
		else if (!ft_strcmp(list->content, "<"))
			list->type = redir_input;
		else if (!ft_strcmp(list->content, "<<"))
			list->type = d_herdoc;
		else if (!ft_strcmp(list->content, ">>"))
			list->type = redir_o_app;
		else if (!ft_strcmp(list->content, "|"))
			list->type = pipe_line;
		else
			list->type = word;
		list = list->next;
	}
	return (NULL);
}
