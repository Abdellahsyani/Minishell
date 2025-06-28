/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:04:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/28 16:38:41 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_value(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		else
			env->value = NULL;
		i++;
	}
	return (0);
}

int	ft_env(t_env **env, char **argv)
{
	t_env	*tmp;

	tmp = NULL;
	update_path(argv[0], env);
	tmp = *env;
	if (!env)
		return (1);
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (tmp->value && ft_strcmp(tmp->key, "?"))
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
