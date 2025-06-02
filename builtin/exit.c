/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:54:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/02 13:02:01 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exit(char **arg, int last_status)
{
    int i;

    i = 0;
    if (arg[0] && arg[1] && arg[2])
    {
        printf("exit : too many arguments\n");
        exit (2);
    }
    if (arg[1])
    {
        while (arg[1][i])
        {
            if (arg[1][i] < '0' && arg[1][i] > '9')
            {
                printf("exit : required only numbers\n");
                exit (2);
            }
            i++;
        }
        exit(ft_atoi(arg[1]));
    }
    exit(last_status);
}
