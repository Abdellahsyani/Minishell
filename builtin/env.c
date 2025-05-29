/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:04:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/23 17:37:13 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int ft_env(t_env **env)
{
    t_env *tmp;
    
    tmp = *env;
    if (!tmp)
        return (1);
    while(tmp)
    {
        printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
    return (0);
}
// int main(int ac, char **args, char **env)
// {
//     (void)ac;
//     (void)args;
//     t_env **envp;

//     envp = get_env(env);
//     return (ft_env(envp));
// 
