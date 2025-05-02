/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:46:01 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/02 18:46:51 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_value(t_env *env, char *str)
{
    t_env *tmp;
    
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

static char *cd_get_target(char **args, t_env *env)
{
    char *target;
    
    if (!args[1])
    {
        target= get_env_value(env, "HOME");
        if(!target)
        {
            printf("cd: HOME not set\n");
            return (NULL);
        }
    }
    else
        target = args[1];
    return (target);
}

void    set_pwd_env(t_env **env, char *key,char *value)
{
    t_env *list;
    
    list = find(*env, key);
    if (list)
    {
        free(list->value);
        list->value = ft_strdup(value);
    }
    else
    {
        printf("key not exist\n");
        return ;
    }
}
static int cd_update_env(t_env *env, char *str,char *target)
{
    char *new;
    
    new = getcwd(NULL, 0);
    if(!new)
    {
        printf("cd: getcwd failed\n");
        return (0);
    }
    set_pwd_env(&env, "PWD", new);
    free(new);
    return (1);
}
static int cd_change_directory(t_env *env, char *target)
{
    char *cwd;
    
    cwd = getcwd(NULL,0);
    if (!cwd)
    {
        printf("cd: getcwd failed\n");
        return 0;
    }
    set_pwd_env(&env,"OLDPWD",cwd);
    free(cwd);
    if (chdir(target) != 0)
    {
        printf("cd : %s : %s\n",target,strerror(errno));
        return (0);
    }
    return (cd_update_env(env,"PWD", target));
    
}

int cd(char **args, t_env *env)
{
    char *target;
    
    target = cd_get_target(args,env);
    if(!target)
    {
        return 0;
    }
    return (cd_change_directory(env, target));
}
