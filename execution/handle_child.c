/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:49:49 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/20 18:32:40 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_handle1(t_redi *tmp, t_extra ptr)
{
	int	fd;

	if (!tmp)
	{
		if (ptr.i != ptr.size)
		{
			dup2(ptr.pipline[ptr.i][1], 1);
		}
	}
	while (tmp)
	{
		if (pass_out(tmp, &fd) == 1)
		{
			dup2(fd, 1);
			close(fd);
		}
		tmp = tmp->next;
	}
}

void	pass_in(t_redi *tmp, int fd)
{
	if (fd == -3)
		fd = open(tmp->file, O_RDONLY);
	if (fd == -1)
	{
		write(1, "minishell: ", 11);
		perror(tmp->file);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void	input_handle1(t_redi *in, t_extra ptr, int fd)
{
	if (!in)
	{
		if (ptr.i != 0)
			dup2(ptr.pipline[ptr.i - 1][0], 0);
		return ;
	}
	while (in)
	{
		if (in->type == redir_input)
			pass_in(in, -3);
		else if (in->type == d_herdoc && !in->next)
			pass_in(in, fd);
		in = in->next;
	}
}

void	exec_cmd(t_command *cmd, t_extra ptr)
{
	int		status;
	char	*path;

	if (is_builtin(cmd))
	{
		status = ft_exec_builtin(cmd->argv[0], cmd->argv, ptr.env);
		update_exit_status(ptr.env, status);
		exit(status);
	}
	else
	{
		if (cmd->argv[0] == NULL)
			return ;
		path = find_path(cmd->argv[0], ptr.env);
		if (!path)
		{
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			clean_all(ptr.env, 127, 0);
		}
		execve(path, cmd->argv, ptr.envp);
		perror("execve failed.");
		exit(127);
	}
}

void	handle_child(t_command *cmd, t_extra ptr)
{
	input_handle1(cmd->in, ptr, cmd->fd);
	output_handle1(cmd->out, ptr);
	closingfds(ptr.pipline, ptr.size);
	if (cmd->argv != NULL)
	{
		exec_cmd(cmd, ptr);
	}
	exit(0);
}
