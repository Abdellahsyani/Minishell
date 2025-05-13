/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:55:21 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/13 17:10:00 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    write_in_file(int fd, char **cmd, char *limiter)
{
    char *line;
    int i;
    while (1)
    {
        
        write(fd, "> ", 2);
        line = readline(cmd[1]);
       
        i = 0;
        i  = ft_strlen(line);
        write(fd, line, i);
        write(fd,"\n", 1);
        if (!ft_strcmp(limiter, line))
        break;
    }
}

int ft_handle_herdoc(char **cmd) //int ft_handle_herdoc(char **cmd, t_redi *in)
{
    int fd;
    char    *limiter;
    // if (in->file == NULL)
    //     return (1);
    limiter = ft_strdup(cmd[1]);
    fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0640);
    if (fd == -1)
    {
        printf("open failed\n");
        return (1);
    }
    write_in_file(fd,cmd, limiter);
    return (0);
}

// void    ft_herdoc(t_command **cmd, t_extra *ptr)
// {
//     t_command *tmp;
//     t_redi *in;


//     while (tmp)
//     {
//         in = tmp->type;
//         while (in)
//         {
//             if (in->type = d_herdoc)
//                 ptr->fd = ft_handle_herdoc(cmd,in);
//             in = in->next;
//         }
//         tmp = tmp->next;
//     }
// }

int main(int ac, char **arg)
{
    if (ac < 2)
        return (1);
    if (ft_handle_herdoc(arg))
        return (1);
    return 0;
}