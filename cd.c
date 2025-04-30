/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:46:01 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/30 11:46:50 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(s_env *env, char *str)
{
    s_env *tmp;
    
    tmp = env;
    if (!str || !*str)
        return ("");
    while (tmp)
    {
        if (!strcmp(tmp->key, str))
            return (tmp->value);
        tmp = tmp->next;
    }
    return ("");
}
char *cd_get_target(char **args, s_env *env)
{
    char *target;
    
    if (!args[1])
    {
        target= get_env_value(env, "HOME");
        if(!*target)
        {
            //insert
            return (NULL);
        }
    }
    else
        target = args[1];
    return (target);
}
int cd_update_env(s_env *env, char *str,char *target)
{
    char *new;
    
    new = getcwd(NULL, 0);
    if(!new)
    {
        pritnf ("cd: getcwd failed\n");
        free(new);
        return (0);
    }
    set_pwd_env(env, "PWD", new); //does not implement yet
    return (1);
}
int cd_change_directory(s_env *env, char *target)
{
    char *cwd;
    
    cwd = getcwd(NULL,0);
    if (!cwd)
    {
        printf("cd: getcwd failed\n");
        free(cwd);
        return 0;
    }
    set_pwd_env(env,"OLDPWD",cwd);// does not impliment yet
    if (chdir(target) != 0)
    {
        printf("cd : chdir failed\n");
        free(cwd);
        return (0);
    }
    return (cd_update_env(env,"PWD", target));
    
}

int cd(char **args, s_env *env)
{
    char *target;
    
    target = cd_get_target(args,env);
    if(!target)
    {
        return 0;
    }
    return (cd_change_directory(env, target));
}
