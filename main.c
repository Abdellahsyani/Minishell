/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:06 by asyani            #+#    #+#             */
/*   Updated: 2025/05/01 13:53:29 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char	*line;
	char	type;
	t_token	*list = NULL;
	t_token *tmp = NULL;

	while (1)
	{
		line = readline("\033[1;32m minishell $ \033[0m");
		if (line)
			add_history(line);
		get_input(line, &list);
		tmp = list;
		while (tmp)
		{
			type = token_type(tmp->content);
			printf("%c: %s\n", type, tmp->content);
			tmp = tmp->next;
		}
	}
	return (0);
}
