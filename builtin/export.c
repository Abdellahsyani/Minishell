/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:52:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/27 14:30:41 by abhimi           ###   ########.fr       */
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
		if (!tmp->value)
		{
			printf("declare -x %s\n",tmp->key);
		}
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
		create = malloc(sizeof(t_env));
		create->key = ft_strdup(key);
		create->value= ft_strdup(value);
		create->next = *env;
		*env = create;
	}
}

char	*extract_space(char *str)
{
	int	i;
	char	*value;
	int count = 0;
	int j = 0;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			count++;
		i++;
	}
	i = 0;
	value = gc_malloc(sizeof(count) + 1);
	while (str[i])
	{
		if ((str[i] == ' ' && str[i + 1] == ' ') || str[i] == '"')
		{
			i++;
			continue;
		}
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

int check_arg(char *str,t_env **env)
{
	int i;
	char *key;
	char *value = NULL;
	int l;
	l = ft_strlen(str);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (!is_valid(key))
		return (free(key), 0);
	if (str[i] == '=')
	{
		if (str[i + 2] == ' ')
		{
			i += 2;
			value = ft_substr(str, i, l - i - 1);
		}
		else
			value = extract_space(&str[i + 1]);
	}
	printf("value: %s\n", value);
	set_new_env(key, value,env);
	return (1);
}

int ft_export(char **arg, t_env **env)
	{
		int i;

		i = 1;
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
					// return (0);
				}
				i++;    
			}
		}
		return (1);
	}
