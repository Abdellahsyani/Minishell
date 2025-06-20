/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:55:21 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/20 10:51:50 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_file(int fd, t_env **env, char *limiter)
{
	char	*line;
	char	*err;

	err = "minishell: warning: here-document at\
	line 1 delimited by end-of-file\n";
	while (1)
	{
		line = readline("> ");
		if (!*line)
			continue ;
		if (!line)
		{
			write(2, err, ft_strlen(err));
			free(line);
			clean_all(env, 0, 0);
		}
		if (!ft_strncmp(line, limiter, ft_strlen(line)))
		{
			free(line);
			clean_all(env, 0, 0);
		}
		helper_herdoc(line, fd, env);
		free(line);
	}
}

void	write_to_herdoc(int fd, t_env **env, char *limiter)
{
	char	*delimiter;

	signal(SIGINT, SIG_DFL);
	if (*limiter == '\0')
		delimiter = ft_strjoin(limiter, "\n");
	else
	{
		delimiter = ft_strjoin(limiter, "\n");
	}
	write_in_file(fd, env, delimiter);
	close(fd);
	exit(0);
}

int	ft_handle_herdoc(char *value, t_env **env)
{
	pid_t	pid;
	int		fd;
	int		status;

	pid = fork();
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0774);
	if (pid < 0)
		printf("fork failed.\n");
	else if (pid == 0)
		write_to_herdoc(fd, env, value);
	else
		waitpid(pid, &status, 0);
	unlink("/tmp/heredoc");
	return (fd);
}

void	ft_herdoc(t_command **cmd, t_env **env)
{
	t_command	*tmp;
	t_redi		*in;

	tmp = *cmd;
	tmp->fd = -1;
	while (tmp)
	{
		in = tmp->in;
		tmp->fd = -1;
		while (in)
		{
			if (in->type == d_herdoc)
				tmp->fd = ft_handle_herdoc(in->file, env);
			in = in->next;
		}
		tmp = tmp->next;
	}
}
