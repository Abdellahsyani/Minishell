/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:49:49 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/24 18:23:56 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	output_handle1(t_redi *tmp, t_extra ptr)
{
	int	fd;

	if (!tmp)
	{
		if (ptr.i != ptr.size)
		{
			dup2(ptr.pipline[ptr.i][1], 1);
		}
		return (1);
	}
	while (tmp)
	{
		if (pass_out(tmp, &fd) == 1)
		{
			dup2(fd, 1);
			close(fd);
		}
		else
			return (0);
		tmp = tmp->next;
	}
	return (1);
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
		clean_all(ptr.env, status, 0);
	}
	else
	{
		if (is_regular_executable(cmd->argv[0]) == 2)
			ft_error(ptr.env, cmd->argv[0], " :is directory\n", 126);
		path = find_path(cmd->argv[0], ptr.env);
		if (!path)
			ft_error(ptr.env, cmd->argv[0], ": command not found\n", 127);
		ft_free_env(ptr.env);
		rl_clear_history();
		execve(path, cmd->argv, ptr.envp);
		perror("execve failed.");
		clean_all(ptr.env, 127, 0);
	}
}

void	handle_child(t_command *cmd, t_extra ptr)
{
	signal(SIGINT, handle_child_sig);
	input_handle1(cmd->in, ptr, cmd->fd);
	if (!output_handle1(cmd->out, ptr))
	{
		clean_all(ptr.env, 1, 0);
	}
	closingfds(ptr.pipline, ptr.size);
	if (cmd->argv != NULL && cmd->argv[0])
	{
		exec_cmd(cmd, ptr);
	}
	clean_all(ptr.env, 0, 0);
}
