/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:52:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/01 15:59:06 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *find(t_env *env, char *key)
{
    while (env)
    {
        if (!ft_strcmp(env->key, key))
            return (env);
        env = env->next;  
    }
    return (NULL);
}
void    print_export(t_env **env)
{
    t_env *tmp;

    tmp = *env;
    while (tmp)
    {
        if (!tmp->value)
        {
            printf("declare -x %s\n",tmp->key);
        }
        else
            printf("declare -x %s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
}
void    alloce_env(char *key, char *value, t_env **env)
{
    t_env *exist;
    t_env *create;
    
    exist = find(*env, key);
    if (exist)
    {
        free(exist->value);
        exist->value = ft_strdup(value);
        return ;
    }
    else
    {
        create = malloc(sizeof(t_env));
        create->key = ft_strdup(key);
        free(key);
        create->value= ft_strdup(value);
        free(value);
        create->next = *env;
        *env = create;
    }
}
int check_arg(char *str,t_env **env)
{
    int i;
    char *key;
    char *value;
    int l;
    
    l = ft_strlen(str);
    i = 0;
    while (str[i] != '\0' && str[i] != '=')
        i++;
    
    key = ft_substr(str, 0, i);
    if (str[i] == '=')
    {
        value = ft_substr(str, i + 1, l - i - 1);
        
    }
    if (!is_valid(key))
        return (free(key), free(value), 0);
    else
    {
          alloce_env(key, value,env);
          return (1);
    }
}

int ft_export(char **arg, t_env **env)
{
    int i;
    
    i = 1;
    if (!arg[1])
    {
        print_export(env);
        return (1);
    }
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