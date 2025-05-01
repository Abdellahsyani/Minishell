/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:52:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/01 17:05:13 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_export(s_env *env)
{
    s_env *tmp;

    tmp = env;
    while (tmp)
    {
        printf("declare -x %s=%s",tmp->key,tmp->value);
        tmp = tmp->next;
    }
}

void check_arg(char *str,s_env *env)
{
    char
}

int ft_export(char **arg, s_env *env)
{
   

    i = 1;
    if (!arg[1])
        print_export(env);
    else
    {
        while (arg[i])
        {
            check_arg(arg[i],env)
            // while (arg[i][j] != '=')
            // {
            //     if (!is_valid());
            // }
        
            
        }
        
    }
}