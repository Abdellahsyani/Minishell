/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:46:01 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/03 16:12:38 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_value(t_env *env, char *str)
{
	t_env *tmp;

	tmp = env;
	if (!str || !*str)
		return ("");
	while (tmp)
	{
		if (!strcmp(tmp->key, str))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

static char *cd_get_target(char **args, t_env **env)
{
	char *target;

	if (!args[1])
	{
		target= get_env_value(*env, "HOME");
		if(!target)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else
	target = args[1];
	return (target);
}

void    set_pwd_env(t_env **env, char *key,char *value)
{
	t_env *list;

	list = ft_find(*env, key);
	if (list)
		list->value = value;
	else
	{
		printf("key not exist\n");
		return ;
	}
}

static int cd_update_env(t_env **env, char *str,char *target)
{
	char *new;
	(void)str;
	(void)target;
    new = getcwd(NULL, 0);
 
    if(!new)
    {
        ft_putstr_fd("cd: error retrieving current directory", 2);
		perror("getcwd : cannot access parent directories");
        return (0);
    }
    set_pwd_env(env, "PWD", new);
    return (1);
}
static int cd_change_directory(t_env **env, char *target)
{
	char *cwd;

	cwd = ft_get(env, "OLDPWD");
	if (!cwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		perror("getcwd : cannot access parent directories");
		return 0;
	}
	set_pwd_env(env,"OLDPWD",cwd);
	if (chdir(target) != 0)
	{
		printf("cd : %s : %s\n",target,strerror(errno));
		return (0);
	}
	return (cd_update_env(env,"PWD", target));
}

int ft_cd(char **args, t_env **env)
{
	char *target;

	target = cd_get_target(args,env);
	if(!target)
	{
		return 0;
	}
	return (cd_change_directory(env, target));
}
