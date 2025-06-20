/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:12:20 by asyani            #+#    #+#             */
/*   Updated: 2025/06/18 19:17:39 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_error(char *str, t_env **env)
{
	if (str)
	{
		printf("bash: syntax error near unexpected token `%s`\n", str);
		update_exit_status(env, 2);
	}
	else
	{
		printf("bash: syntax error near unexpected token `newline`\n");
		update_exit_status(env, 2);
	}
	return (0);
}

static int	is_consecutive_operator(t_token *list)
{
	if (!list || !list->next)
		return (1);
	while (list && list->type != word)
	{
		if (list->next && (list->type == list->next->type))
		{
			return (0);
		}
		list = list->next;
	}
	return (1);
}

int	op_error_syntax(t_token *list, t_env **env)
{
	if (list && is_consecutive_operator(list) == 0)
		return (print_error(list->content, env));
	if (list && list->type != pipe_line)
	{
		if (list->next && list->next->type != word)
		{
			list = list->next;
			if (list->next == NULL)
				return (print_error(list->content, env));
		}
		if (list->next == NULL)
			return (print_error(NULL, env));
	}
	return (1);
}

int	start_parsing(t_token *list, t_env **env)
{
	t_token	*current;
	int		error;

	current = list;
	error = 1;
	if (!list)
		return (0);
	if (list->type == pipe_line && !list->next)
		return (print_error(list->content, env));
	while (current)
	{
		if (current->type == word)
			current = current->next;
		else
		{
			error = op_error_syntax(current, env);
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
		if (list->type != word && list->next->type == word)
			return (count);
		if (list->type == word)
			count++;
		list = list->next;
	}
	return (count);
}

t_command	*create_cmd_node(int count)
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

void	add_to_argv(t_command *cmd, char *str)
{
	int	i;

	i = 0;
	if (!cmd || !str || !cmd->argv_t)
		return ;
	while (cmd->argv_t[i] != NULL)
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

char	*rem_double(char *content)
{
	int	i;
	char	*var;
	int	len;

	i = 1;
	len = ft_strlen(content);
	var = ft_strlcpy(NULL, content, len - 2, i);
	return (var);
}

void	fill_operation(t_command *cmd, t_token **cur, int i)
{
	t_redi	*new_redi;
	char	*var;

	if (!(*cur) || !(*cur)->next)
		return ;
	var = rem_double((*cur)->next->content);
	if (i == 1)
	{
		new_redi = create_nod();
		new_redi->file = ft_strdup(var);
		new_redi->type = (*cur)->type;
		add_lis(&cmd->in, new_redi);
	}
	else if (i == 0)
	{
		new_redi = create_nod();
		new_redi->file = ft_strdup(var);
		new_redi->type = (*cur)->type;
		add_lis(&cmd->out, new_redi);
	}
}

void	create_new_node(int count, t_command **cmd, t_command **cur)
{
	add_cmd_list(count, cmd);
	*cur = get_last_cmd(*cmd);
	if (!cur)
		return ;
}

void	check_args(t_token *current, t_command **cmd, t_command **list)
{
	int	count;

	count = 0;
	if (current->type == word)
		count = count_word_tokens(current);
	if (*cmd == NULL)
		create_new_node(count, list, cmd);
	if (current->type == word)
		add_to_argv(*cmd, current->content);
}

void	pars_command(t_token *list, t_command **cmd_list)
{
	t_command	*current_cmd;
	t_token		*current;

	current_cmd = NULL;
	current = list;
	while (current)
	{
		check_args(current, &current_cmd, cmd_list);
		if ((current->type == redir_output || current->type == redir_o_app)
			&& current->next)
		{
			fill_operation(current_cmd, &current, 0);
			if (!current->next->next)
				break ;
			current = current->next->next;
			continue ;
		}
		else if ((current->type == redir_input || current->type == d_herdoc)
			&& current->next)
		{
			fill_operation(current_cmd, &current, 1);
			if (!current->next->next)
				break ;
			current = current->next->next;
			continue ;
		}
		else if (current->type == pipe_line)
			current_cmd = NULL;
		if (current)
			current = current->next;
	}
}
