/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:57:42 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/13 14:02:44 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cmd_size(t_command **cmd)
{
    t_command *tmp;
    int count;
    if (!*cmd)
        return (0);
    tmp = *cmd;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    return(count);
}

int ft_exec(t_command **cmd)
{
    t_extra ptr;
    t_command *str;
    
    ptr.size = ft_cmd_size(cmd);
    ptr.i = 0;
    ft_herdoc(cmd, &ptr);
    
}