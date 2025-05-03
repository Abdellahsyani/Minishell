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

int	start_parsing(t_token *list)
{
	while (list)
	{
		if (!ft_strcmp(token_type(list->content), "pipe_line"))
		{
	   		printf("syntax error\n");
	   		return (0);
	   	}
		else if (!ft_strcmp(token_type(list->content), "))
	}
}
