/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:28:58 by asyani            #+#    #+#             */
/*   Updated: 2025/06/21 18:30:57 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_command	*create_cmd_node(int count)
{
	t_command	*new_node;

	new_node = gc_malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->in = NULL;
	new_node->out = NULL;
	new_node->argv = NULL;
	new_node->argv_t = NULL;
	if (count > 0)
	{
		new_node->argv_t = gc_malloc(sizeof(char *) * (count + 2));
		if (!new_node->argv_t)
			return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	add_cmd_list(int count, t_command **cmd)
{
	t_command	*new_node;
	t_command	*tmp;

	new_node = create_cmd_node(count);
	if (*cmd == NULL)
		*cmd = new_node;
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

static t_command	*get_last_cmd(t_command *cmd_list)
{
	if (!cmd_list)
		return (NULL);
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	return (cmd_list);
}

void	create_new_node(int count, t_command **cmd, t_command **cur)
{
	add_cmd_list(count, cmd);
	*cur = get_last_cmd(*cmd);
	if (!cur)
		return ;
}

char	*rem_double(char *content)
{
	int		i;
	char	*var;
	int		len;

	i = 1;
	len = ft_strlen(content);
	var = ft_strlcpy(NULL, content, len - 2, i);
	return (var);
}
