/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:12:20 by asyani            #+#    #+#             */
/*   Updated: 2025/06/21 18:36:00 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_ops(char *var, t_token **cur, t_redi **new_redi)
{
	*new_redi = create_nod();
	if (var)
		(*new_redi)->file = ft_strdup(var);
	else
		(*new_redi)->file = ft_strdup((*cur)->next->content);
	(*new_redi)->type = (*cur)->type;
}

static void	fill_operation(t_command *cmd, t_token **cur, int i, t_env **env)
{
	t_redi	*new_redi;
	char	*var;

	var = NULL;
	new_redi = NULL;
	var = split_part(cur, (*cur)->next->content, env, 0);
	if ((*env)->flag == -1)
		return ;
	if (i == 1)
	{
		fill_ops(var, cur, &new_redi);
		add_lis(&cmd->in, new_redi);
	}
	else if (i == 0)
	{
		fill_ops(var, cur, &new_redi);
		add_lis(&cmd->out, new_redi);
	}
}

static void	check_args(t_token *current, t_command **cmd, t_command **list)
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

static void	pars_cmd2(t_token *cur, t_command *c_cmd, t_command **cmd_l,
		t_env **en)
{
	while (cur)
	{
		check_args(cur, &c_cmd, cmd_l);
		if ((cur->type == redir_output || cur->type == redir_o_app)
			&& cur->next)
		{
			fill_operation(c_cmd, &cur, 0, en);
			if (!cur->next->next)
				break ;
			cur = cur->next->next;
			continue ;
		}
		else if ((cur->type == redir_input || cur->type == d_herdoc)
			&& cur->next)
		{
			fill_operation(c_cmd, &cur, 1, en);
			if (!cur->next->next)
				break ;
			cur = cur->next->next;
			continue ;
		}
		else if (cur->type == pipe_line)
			c_cmd = NULL;
		if (cur)
			cur = cur->next;
	}
}

void	pars_command(t_token *list, t_command **cmd_list, t_env **env)
{
	t_command	*current_cmd;
	t_token		*current;

	(*env)->flag = 0;
	current_cmd = NULL;
	current = list;
	pars_cmd2(current, current_cmd, cmd_list, env);
}
