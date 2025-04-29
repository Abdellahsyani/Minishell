/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:46:01 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/29 17:09:47 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *get_env_value(char *env, char *str)
{
    int i;
    char *path;
}
char *cd_get_target(char **args, char *env)
{
    char *target;
    
    if (!args[1])
    {
        target= get_env_value(env, "HOME");
    }
    else
        target = args[1];
}

int cd(char **args, char *env)
{
    char *target;
    
    target = cd_get_target(args,env);
    if(!target)
    {
        return 0;
    }
    // ft_update_pwd()
}