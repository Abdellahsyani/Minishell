/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:44:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/05 13:45:13 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

#include <stdio.h>

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
        if (!arg[i + 1])
        {
            printf("%s",arg[i]);
            break ;
        }
        else
            printf("%s ", arg[i]);
        i++;
    }
}

int    ft_echo(char **arg)
{
    int i;
    int flag;
    
    if (!arg[1])
    {
        printf("\n");
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
            if(!arg[i + 1])
            {    printf("%s\n",arg[i]);
                break;
            }
            else
                printf("%s ",arg[i]);
            i++;
        }
    }
    return (0);
}

int main(int ac, char **arg)
{
    (void)ac;
    
    ft_echo(arg);
    return 0;
}
