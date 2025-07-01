/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:44:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/20 09:49:40 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_flag(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static void	ft_handle_n(char **arg)
{
	int	i;
	int	flag;

	i = 2;
	flag = 0;
	while (arg[i])
	{
		if ((ft_strcmp(arg[i], "-n") == 0 || ft_check_flag(arg[i]))
			&& flag == 0)
		{
			i++;
			continue ;
		}
		flag = 1;
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1] && arg[i][0] != '$')
			ft_putstr_fd(" ", 1);
		i++;
	}
}

int	ft_echo(char **arg)
{
	int	i;
	int	flag;

	if (!arg[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	flag = ft_check_flag(arg[1]);
	if (flag)
		ft_handle_n(arg);
	else
	{
		i = 1;
		while (arg[i])
		{
			ft_putstr_fd(arg[i], 1);
			if (arg[i + 1] && arg[i][0] != '$' && arg[i][0] != '\0')
				ft_putstr_fd(" ", 1);
			i++;
		}
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
