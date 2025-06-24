/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:33:19 by asyani            #+#    #+#             */
/*   Updated: 2025/06/24 15:33:56 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_whitespace(char *str)
{
	int	len;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n'))
		str[--len] = '\0';
	return (str);
}

void	ft_free_env(t_env **p)
{
	t_env	*tmp;

	while (*p)
	{
		tmp = *p;
		(*p) = (*p)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(p);
}

void	clean_all(t_env **env, int n, int flag)
{
	(void)flag;
	ft_free_env(env);
	gc_free_all();
	rl_clear_history();
	// if (flag)
	// 	write(2, "exit\n", 5);
	exit(n);
}
