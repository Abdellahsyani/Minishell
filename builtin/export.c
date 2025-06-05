/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:52:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/05 09:55:43 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *ft_find(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;  
	}
	return (NULL);
}

void    print_export(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (!strcmp(tmp->key, "_") || !strcmp(tmp->key, "?"))
		{
			tmp = tmp->next;
			continue ;
		}
		if (!tmp->value)
			printf("declare -x %s\n",tmp->key);
		else
			printf("declare -x %s=\"%s\"\n",tmp->key,tmp->value);
		tmp = tmp->next;
	}
}

void    set_new_env(char *key, char *value, t_env **env)
{
	t_env *exist;
	t_env *create;

	exist = ft_find(*env, key);
	if (exist)
	{
		free(exist->value);
		exist->value = ft_strdup(value);
		return ;
	}
	else
	{
		create = gc_malloc(sizeof(t_env));
		create->key = ft_strdup(key);
		if(value)
			create->value= ft_strdup(value);
		create->next = *env;
		
		*env = create;
	}
}

int check_arg(char *str,t_env **env)
{
	int i;
	char *key;
	char *value;
	int l;
	
	value = NULL;
	l = ft_strlen(str);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (!is_valid(key))
		return (free(key), 0);
	if (str[i] == '=')
	{
		i += 1;
		value = ft_substr(str, i, l - i);
	}
	set_new_env(key, value, env);
	return (1);
}

int ft_export(char **arg, t_env **env)
{
	int i;

	i = 1;
	update_path(arg[0], env);
	if (!arg[1])
	{
		print_export(env);
		return (1);
	}
	else
	{
		while (arg[i])
		{
			if (!check_arg(arg[i],env))
			{
				printf("minishell:export: '%s' : not a valid identifier\n", arg[i]);
			}
			i++;    
			}
	}
		return (1);
}
