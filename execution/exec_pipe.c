/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:57:42 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/09 16:58:25 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int ft_pipe(t_command *cmd)
{
    int pid;
    int stat;
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe\n");
        return (1);
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
        return (ft_child_p(cmd));
    else
        return (ft_parent_p(cmd));
}