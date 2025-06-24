/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:57:42 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/24 17:12:59 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtins(t_command **cmd, t_env **env, int fd)
{
	int			status;
	t_command	*tmp;

	tmp = *cmd;
	if (!redirect_handler(&fd, cmd, env))
		return ;
	status = ft_exec_builtin(tmp->argv[0], tmp->argv, env);
	update_exit_status(env, status);
	if (fd != -2)
	{
		dup2(fd, 1);
		close(fd);
	}
}

int	set_pipes(int **tube, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pipe(tube[i]) == -1)
		{
			closingfds(tube, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	**built_pipline(t_command **cmd, t_env **env, int size)
{
	t_command	*tmp;
	int			**tube;
	int			fd;

	tube = NULL;
	fd = -1;
	tmp = *cmd;
	if (size == 0 && is_builtin(tmp) && tmp->argv)
	{
		exec_builtins(cmd, env, fd);
		return (NULL);
	}
	tube = allocate_tube(size);
	if (!tube)
		return (NULL);
	if (!tube || !set_pipes(tube, size))
	{
		printf("Error: pipe failed or allocation.\n");
		update_exit_status(env, 1);
		closingfds(tube, size);
		return (NULL);
	}
	return (tube);
}

static void	ft_fork(t_extra ptr, t_env **env, t_command *tmp)
{
	ptr.envp = chr_envirment(env);
	while (ptr.i <= ptr.size)
	{
		ptr.pid[ptr.i] = fork();
		if (ptr.pid[ptr.i] == 0)
			handle_child(tmp, ptr);
		ptr.i++;
		tmp = tmp->next;
	}
	wait_and_free(ptr);
}

void	ft_exec(t_command **cmd, t_env **env)
{
	t_extra		ptr;
	t_command	*tmp;

	tmp = *cmd;
	ptr.size = ft_cmd_size(cmd) - 1;
	init_extra(&ptr, env);
	ft_herdoc(cmd, &ptr);
	if (ptr.flag_sig == 1)
	{
		gc_free_all();
		return ;
	}
	ptr.pipline = built_pipline(cmd, env, ptr.size);
	if (!ptr.pipline)
	{
		gc_free_all();
		return ;
	}
	ptr.pid = gc_malloc(sizeof(pid_t) * (ptr.size + 1));
	if (!ptr.pid)
		return ;
	ft_fork(ptr, env, tmp);
}
