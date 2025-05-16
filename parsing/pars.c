/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:12:20 by asyani            #+#    #+#             */
/*   Updated: 2025/05/03 15:14:22 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_error(char *str)
{
	printf("bash: syntax error near unexpected token `%s`\n", str);
	return (0);
}

int	op_error_syntax(t_token *list)
{
	if (list && list->type != pipe_line)
	{
		if (list->next && list->next->type != word)
		{
			list = list->next;
			if (list->next == NULL)
				return (print_error(list->content));
		}
		if (list->next == NULL)
			return (print_error("newline"));
	}
	else if (list && list->type == pipe_line)
	{
		if (list->next != NULL && list->type == word)
			return (print_error(list->content));
	}
	return (1);
}

int	start_parsing(t_token *list)
{
	t_token	*current;
	int	error;

	current = list;
	error = 1;
	if (!list)
		return (0);
	if (list->type == pipe_line)
		return (print_error(list->content));
	while (current)
	{
		if (current->type == word)
			current = current->next;
		else
		{
			error = op_error_syntax(current);
			if (!error)
				return (0);
			current = current->next;
		}
	}
	return (1);
}

int	count_word_tokens(t_token *list)
{
	int	count;

	count = 0;
	while (list && list->type != pipe_line)
	{
		if (list->type == word)
			count++;
		list = list->next;
	}
	return count;
}

t_command	*create_cmd_node(t_token *list)
{
	t_command	*new_node;
	int	count;

	count = count_word_tokens(list);
	new_node = gc_malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->argv_t = gc_malloc(sizeof(char *) * (count + 1));
	if (!new_node->argv_t)
		return (NULL);
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->append = 0;
	new_node->next = NULL;
	return (new_node);
}

void	add_cmd_list(t_token *list, t_command **cmd)
{
	t_command	*new_node;

	new_node = create_cmd_node(list);
	if (*cmd == NULL)
		*cmd = new_node;
	else
	{
		t_command *tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	add_to_argv(t_command *cmd, char *str)
{
	int	i;

	i = 0;
	if (!cmd || !str)
		return ;
	/*printf("argv[0] = %s\n",cmd->argv_t[i]);*/
	while (cmd->argv_t[i])
		i++;
	cmd->argv_t[i] = ft_strdup(str);
	cmd->argv_t[i + 1] = NULL;
}

t_command	*get_last_cmd(t_command *cmd_list)
{
	if (!cmd_list)
		return (NULL);
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	return (cmd_list);
}

void	fill_operation(t_command *cmd, t_token **cur, int i)
{
	if (i == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup((*cur)->next->content);
		cmd->append = 0;
		*cur = (*cur)->next;
	}
	if (i == 1)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup((*cur)->next->content);
		cmd->append = 1;
		*cur = (*cur)->next;
	}
	if (i == 2)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup((*cur)->next->content);
		*cur = (*cur)->next;
	}
}

int pars_command(t_token *list, t_command **cmd_list)
{
	t_command *current_cmd = NULL;
	t_token *current = list;

	while (current)
	{
		if (current_cmd == NULL)
		{
			add_cmd_list(list, cmd_list);
			current_cmd = get_last_cmd(*cmd_list);
			if (!current_cmd)
				return (0);
		}
		if (current->type == word)
			add_to_argv(current_cmd, current->content);
		else if (current->type == redir_output && current->next)
				fill_operation(current_cmd, &current, 0);
		else if (current->type == redir_input && current->next)
				fill_operation(current_cmd, &current, 2);
		else if (current->type == redir_o_app && current->next)
			fill_operation(current_cmd, &current, 1);
		else if (current->type == pipe_line)
			current_cmd = NULL;
		if (current)
			current = current->next;
	}
	return (1);
}
