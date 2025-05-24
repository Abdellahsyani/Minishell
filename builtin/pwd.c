/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:50:39 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/23 17:38:02 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(char **args)
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
    path = getcwd(NULL, 0);
    if(!path)
    {
        printf("pwd: getcwd failed\n");
        free(path);
        return (0);
    }
    printf("%s\n", path);
    free(path);
    return (1);
}
