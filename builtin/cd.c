/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:46:01 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/20 10:39:56 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_get_target(char **args, t_env **env)
{
	char	*target;

	if (!args[1])
	{
		target = ft_get(env, "HOME");
		if (!target)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else
		target = args[1];
	return (target);
}

void	set_pwd_env(t_env **env, char *key, char *value)
{
	t_env	*list;

	list = ft_find(*env, key);
	if (list)
		list->value = value;
	else
	{
		printf("key not exist\n");
		return ;
	}
}

static int	cd_update_env(t_env **env, char *str, char *target)
{
	char	*new;

	(void)str;
	(void)target;
	new = getcwd(NULL, 0);
	if (!new)
	{
		ft_putstr_fd("cd: error retrieving current directory", 2);
		perror("getcwd : cannot access parent directories");
		return (1);
	}
	set_pwd_env(env, "PWD", new);
	return (0);
}

static int	cd_change_directory(t_env **env, char *target)
{
	char	*cwd;

	cwd = ft_get(env, "OLDPWD");
	if (!cwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		perror("getcwd : cannot access parent directories");
		return (1);
	}
	set_pwd_env(env, "OLDPWD", cwd);
	if (chdir(target) != 0)
	{
		printf("cd : %s : %s\n", target, strerror(errno));
		return (1);
	}
	return (cd_update_env(env, "PWD", target));
}

int	ft_cd(char **args, t_env **env)
{
	char	*target;

	if (args[2])
	{
		ft_putstr_fd("too many arguments", 2);
		update_exit_status(env, 1);
		return (1);
	}
	target = cd_get_target(args, env);
	if (!target)
	{
		return (0);
	}
	return (cd_change_directory(env, target));
}
