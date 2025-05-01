/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:52:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/01 18:38:17 by abhimi           ###   ########.fr       */
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

int check_arg(char *str,s_env *env)
{
    int i;
    char *key;
    char *value;
    int l;
    
    l = ft_strlen(str);
    i = 0;
    while (str[i] != '\0' || str[i] != '=')
        i++;
    
    key = ft_substr(str, 0, i);
    if (str[i] == '=')
    {
        i++;
        value = ft_substr(str, i, l);
        
    }
    if (!is_valid(key))
        return (free(key), free(value), 0);
    else
    {
          alloce_env(key, value,env);//no implement yet
          return (1);
    }
}

int ft_export(char **arg, s_env *env)
{
    int i;
    
    i = 1;
    if (!arg[1])
        print_export(env);
    else
    {
        while (arg[i])
        {
            if (!check_arg(arg[i],env))
            {
                printf("minishell:export: %s : not a valid identifier", arg[i]);
                return (0);
            }
            i++;    
        }
    }
    return (1);
}