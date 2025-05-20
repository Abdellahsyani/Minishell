/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:32:15 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/18 01:46:58 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exec_builtin(char *cmd, char **args, t_env **env)
{
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
    else if (!ft_strcmp(cmd, "exit"))
        return (ft_exit(args, 0));
    return (1);
}

int is_builtin(t_command *cmd)
{
    if (!ft_strcmp(cmd->arg[0], "echo") || !ft_strcmp(cmd->arg[0], "cd"))
        return (1);
    else if (!ft_strcmp(cmd->arg[0], "export") || !ft_strcmp(cmd->arg[0], "unset"))
        return (1);
    else if (!ft_strcmp(cmd->arg[0], "env") || !ft_strcmp(cmd->arg[0], "pwd"))
        return (1);
    else if (!ft_strcmp(cmd->arg[0], "exit"))
        return (1);
    return (0);
}
