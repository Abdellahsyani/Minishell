/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:50:39 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/03 13:30:56 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(char **args, t_env **env)
{
    int i;
    char *path;

    i = 1;
    
    while(args[i])
    {
        if (args[i][0] != ' ' && args[i][0] != '\0')
        {
            printf("pwd : too many arguments\n");
            return (0);
        }
        i++;
    }
    path = ft_get(env, "PWD");
    if(!path)
    {
        printf("pwd: getcwd failed\n");
        free(path);
        return (0);
    }
    printf("%s\n", path);
    return (1);
}