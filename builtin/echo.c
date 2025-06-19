/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:44:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/19 17:28:04 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_check_flag(char **arg)
{
    int i;
    
    i = 1;
    if (arg[1][0] == '-')
    {
        while (arg[1][i])
        {
            if (arg[1][i] != 'n')
                return (0);
            i++;
        }
        return 1;
    }
        
    return 0;
}

static void    ft_handle_n(char **arg)
{
    int i;

    i = 2;
    
    while (arg[i])
    {
        ft_putstr_fd(arg[i], 1);
        if (arg[i + 1])
                ft_putstr_fd(" ", 1);
        i++;
    }
}

int    ft_echo(char **arg)
{
    int i;
    int flag;
    if (!arg[1])
    {
        ft_putstr_fd("\n", 1);
        return (0);
    }
    flag = ft_check_flag(arg);
    if (flag)
        ft_handle_n(arg);
    else
    {
        i = 1;
        while (arg[i])
        {
             ft_putstr_fd(arg[i], 1);
            if (arg[i + 1])
                ft_putstr_fd(" ", 1);
            i++;
        }
        ft_putstr_fd("\n", 1);
    }
    return (0);
}
