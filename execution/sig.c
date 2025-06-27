/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:01:58 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/27 11:12:42 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sig(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_child_sig(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	gc_free_all();
	rl_clear_history();
	exit(130);
}

char	*rm_newline(char *limit)
{
	int		l;
	int		i;
	char	*str;

	i = 0;
	if (!*limit)
		return (ft_strdup(""));
	l = ft_strlen(limit);
	str = gc_malloc(sizeof(char) * l);
	while (limit[i] != '\n')
	{
		str[i] = limit[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
