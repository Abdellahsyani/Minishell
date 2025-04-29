/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:51:44 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/29 16:04:36 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int ac, char **arg, char **env)
// {
//     //char *s;
//     (void)arg;
//     (void)ac;
    
//     while (*env)
//     {
//         printf("%s",*env);
//         env++;
//     }
//     return (0);
// }

int env_builtin(char **env)
{
    while(*env)
    {
        printf("%s\n",*env);
        env++;
    }
    return 0;
}