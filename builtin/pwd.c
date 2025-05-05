/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:50:39 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/05 15:17:52 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
    return (1)
}

// int main(int ac,char **arg)
// {
//     (void) ac;
//     ft_pwd(arg);
//     return 0;
// }