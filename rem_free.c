/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:33:19 by asyani            #+#    #+#             */
/*   Updated: 2025/06/27 11:07:18 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_whitespace(char *str)
{
	int		len;
	char	*p;
	char	*str1;

	str1 = str;
	if (!str)
		return (NULL);
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len
				- 1] == '\n'))
		str[--len] = '\0';
	p = ft_strdup(str);
	free(str1);
	return (p);
}

void	clean_all(t_env **env, int n, int flag)
{
	(void)flag;
	(void)env;
	gc_free_all();
	env = NULL;
	rl_clear_history();
	exit(n);
}
