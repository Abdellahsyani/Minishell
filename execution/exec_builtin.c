/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:32:15 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/05 15:37:13 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_builtin(char *cmd, char **args, char **envp)
{
    t_env **env;

    env = get_env(envp);
    if (!ft_strcmp(cmd, "cd"))
        return (cd(args, env));
    else if (!ft_strcmp(cmd, "echo"))
        return (ft_echo(args));
    else if (!ft_strcmp(cmd, "pwd"))
        return (ft_pwd(args));
    else if (!ft_strcmp(cmd, "export"))
        return (ft_export(args, env));
    else if (!ft_strcmp(cmd, "unset"))
        return (ft_unset(args, env));
    else if (!ft_strcmp(cmd, "env"))
        return (ft_env(env));
    else
        return (ft_exit(args, 0));
    
}
