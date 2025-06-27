/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:32:53 by asyani            #+#    #+#             */
/*   Updated: 2025/06/27 15:07:55 by abdo             ###   ########.fr       */
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
	if (list->type == pipe_line && (!list->next || list->next))
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

char	*split_part(t_token **cur, char *content, t_env **env, int i)
{
	char	**spl;
	char	*var;

	spl = NULL;
	var = NULL;
	if (!(*cur) || !(*cur)->next)
		return (NULL);
	if (content[0] == '"')
		var = rem_double(content);
	if (content[0] == '$')
	{
		var = get_var(&content[0], env, 1);
		spl = ft_split(var, ' ');
		while (spl[i])
			i++;
		if (i > 1)
		{
			printf("minishell: %s: ambiguous redirect\n", content);
			update_exit_status(env, 1);
			return ((*env)->flag = -1, NULL);
		}
	}
	if (content[0] == '"' && content[1] == '$')
		var = double_quote(&content[0], env);
	return (var);
}
