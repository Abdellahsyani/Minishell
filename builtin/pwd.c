/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:50:39 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/10 19:14:36 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_env **env)
{
    char *path;
 
    path = ft_get(env, "PWD");
    if(!path)
    {
        printf("pwd: getcwd failed\n");
        update_exit_status(env, 1);
        free(path);
        return (1);
    }
    printf("%s\n", path);
    update_exit_status(env, 0);
    return (0);
} 