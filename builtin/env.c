/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:04:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/02 14:28:28 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int ft_check_value(char *str, t_env *env)
{
	int i;

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


int ft_env(t_env **env, char **argv)
{
	t_env *tmp = NULL;
	(void)argv;
	int i;

	i = 1;
	update_path(argv[0], env);
	tmp = *env;
	if (!tmp)
		return (1);
	while(tmp)
	{
		if (tmp->value && strcmp(tmp->key, "?"))
			printf("%s=%s\n",tmp->key,tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
