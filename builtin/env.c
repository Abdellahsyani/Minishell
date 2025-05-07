/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:51:44 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/06 13:50:58 by abhimi           ###   ########.fr       */
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
// }