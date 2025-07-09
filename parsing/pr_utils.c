/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:02:34 by asyani            #+#    #+#             */
/*   Updated: 2025/06/17 14:44:15 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_lis(t_redi **list, t_redi *new_node)
{
	t_redi	*tmp;

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

void	add_to_argv(t_command *cmd, char *str, int count)
{
	int	i;

	i = 0;
	if (!cmd || !str)
		return ;
	if (!cmd->argv_t)
	{
		cmd->argv_t = gc_malloc(sizeof(char *) * (count + 1));
		if (!cmd->argv_t)
			return ;
	}
	while (cmd->argv_t[i] != NULL)
		i++;
	cmd->argv_t[i] = ft_strdup(str);
	cmd->argv_t[i + 1] = NULL;
}

t_redi	*create_nod(void)
{
	t_redi	*new_node;

	new_node = gc_malloc(sizeof(t_redi));
	if (!new_node)
		return (NULL);
	new_node->file = NULL;
	new_node->type = -1;
	new_node->next = NULL;
	return (new_node);
}

int	count_word_tokens(t_token *list)
{
	int	count;

	count = 0;
	while (list && list->type != pipe_line)
	{
		if (list->type != word && list->next->type == word)
			return (count);
		if (list->type == word)
			count++;
		list = list->next;
	}
	return (count);
}

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		gc_free_one(arr[i]);
		i++;
	}
	gc_free_one(arr);
}
