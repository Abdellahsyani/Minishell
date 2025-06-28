/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:54:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/28 18:15:20 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checknum_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i != 0 && !ft_isdigit(str[i - 1]) && str[i] != ' ' && str[i])
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

void	ft_exit(char **arg, int last_status, t_env **env)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		set_new_env("?", "1", env);
		return ;
	}
	if (arg[1])
	{
		if (!ft_checknum_exit(arg[1]))
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			clean_all(env, 2, 0);
		}
		clean_all(env, ft_atoi(arg[1]), 0);
	}
	clean_all(env, last_status, 1);
}
