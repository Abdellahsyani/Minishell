/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:53:29 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/26 17:47:32 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(char *str)
{
	int	i;

	i = 1;
	if (!str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		return (0);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	delete_key_value(char *key, t_env **env)
{
	t_env	*prev;
	t_env	*cur;

	prev = NULL;
	cur = *env;
	if (!key)
		return ;
	while (cur && cur->next)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (prev == NULL)
				*env = cur->next;
			else
				prev->next = cur->next;
			free(cur->key);
			if (cur->value)
				free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_unset(char **arg, t_env **env)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_check_value(arg[i], *env))
			return (1);
		delete_key_value(arg[i], env);
		i++;
	}
	return (0);
}
