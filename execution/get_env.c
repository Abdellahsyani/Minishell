/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:35:20 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/28 16:49:25 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_key(char *str)
{
	int		i;
	int		j;
	char	*key;

	j = 0;
	i = 0;
	key = NULL;
	while (str[i] && str[i] != '=')
		i++;
	key = gc_malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	while (j < i)
	{
		key[j] = str[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*get_value(char *str)
{
	int		i;
	char	*value;
	int		j;
	int		l;

	value = NULL;
	j = 0;
	i = 0;
	l = strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	if (str[i] == '\0')
		return (NULL);
	value = gc_malloc(sizeof(char) * (l - i + 1));
	if (!value)
		return (NULL);
	while (i < l)
	{
		value[j] = str[i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

t_env	*new_node(char *key, char *value)
{
	t_env	*new;

	new = gc_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_env	**get_env(char **list)
{
	t_env	**tmp;
	t_env	*cur;

	cur = NULL;
	tmp = gc_malloc(sizeof(t_env *));
	if (!tmp)
		return (NULL);
	cur = new_node("?", "0");
	*tmp = cur;
	if (!list || !*list)
	{
		cur->next = new_node("PWD", getcwd(NULL, 0));
		cur->next->next = new_node("_", "env");
	}
	else
	{
		while (*list)
		{
			cur->next = new_node(ft_key(*list), get_value(*list));
			cur = cur->next;
			list++;
		}
	}
	return (tmp);
}
