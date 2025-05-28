/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:04:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/28 11:29:08 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int ft_check_value(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
void ft_remove(char **argv, t_env **env)
{
    char *key;
    int i;
    
    i = 1;
    while (argv[i])
    {
       key = ft_key(argv[i]);
       delete_key_value(key, env);
       free(key);
       i++;
    }
}

int ft_env(t_env **env, char **argv)
{
    t_env *tmp;
    int i;

    i = 1;
    while (argv[i])
    {
        if (!ft_check_value(argv[i]))
        {
            printf("env : \'%s\' : NO such file or directory\n", argv[i]);
            return (1);
        }
        i++;
    }
    if (argv[1])
        ft_export(argv,env);
    update_path(argv[0], env);
    tmp = *env;
    if (!tmp)
        return (1);
    while(tmp)
    {
        printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
    ft_remove(argv, env);
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