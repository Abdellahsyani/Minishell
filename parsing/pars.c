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
		if (list->next != NULL)
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
	return (0);
}
