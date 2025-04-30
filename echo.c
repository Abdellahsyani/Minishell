/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:44:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/30 12:59:43 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

#include <stdio.h>

void    ft_echo(char **arg)
{
    int i;

    int flag;
    if (!arg[1])
    {
        printf("\n");
        return ;
    }
    if (arg[1][0] == '-' && arg[1][1] == 'n' && arg[1][2] == '\0')
    {
            flag = 1;
    }
    else
        flag = 0;
    if (flag)
    {
        i = 2;
        while (arg[i])
        {
            if (!arg[i + 1])
            {
                printf("%s",arg[i]);
                break;
            }
            else
                printf("%s ",arg[i]);
            i++;
        }
    }
    else
    {
        i = 1;
        while (arg[i])
        {
            if(!arg[i +1])
            {    printf("%s\n",arg[i]);
                break;
            }
            else
                printf("%s ",arg[i]);
            i++;
        }
    }
}

int main(int ac, char **arg)
{
    (void)ac;
    
    ft_echo(arg);
    return 0;
}