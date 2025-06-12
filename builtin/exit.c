/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:54:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/12 09:35:52 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exit(char **arg, int last_status)
{
    int i;

    i = 0;
    if (arg[2] != NULL)
    {
        ft_putstr_fd(" too many arguments\n", 2);
        exit (1);
    }
    if (arg[1])
    {
        while (arg[1][i])
        {
            if (arg[1][i] == '+' || arg[1][i] == '-' )
            {
                i++;
                continue;
            }
            if (!ft_isdigit(arg[1][i]))
            {
                ft_putstr_fd(" numeric argument required\n", 2);
                exit (2);
            }
            i++;
        }
        exit(ft_atoi(arg[1]));
    }
    exit(last_status);
}
