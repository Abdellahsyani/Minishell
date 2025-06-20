/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:07:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/20 11:01:34 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_envlen(t_env **env)
{
	int		i;
	t_env	*envy;

	i = 0;
	envy = *env;
	if (!envy)
		return (0);
	while (envy)
	{
		i++;
		(envy) = (envy)->next;
	}
	return (i);
}

char	**chr_envirment(t_env **env)
{
	char	**envp;
	t_env	*tmp;
	char	*str;
	int		i;

	envp = NULL;
	if (!env)
		return (NULL);
	tmp = *env;
	i = ft_envlen(env);
	envp = gc_malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin(str, tmp->value);
		gc_free_one(str);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	update_path(char *arg, t_env **env)
{
	t_env	*tmp;
	char	*new_value;
	char	*value;
	char	*str;
	int		l;

	tmp = ft_find(*env, "_");
	value = ft_strdup(tmp->value);
	l = ft_strlen(value);
	while (l > 0)
	{
		if (value[l] == '/' && value[l - 1] != '.')
		{
			str = ft_substr(value, 0, l + 1);
			break ;
		}
		l--;
	}
	new_value = ft_strjoin(str, arg);
	if (!new_value)
		return ;
	set_new_env("_", new_value, env);
}
