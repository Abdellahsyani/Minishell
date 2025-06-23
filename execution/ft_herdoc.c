/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:55:21 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/23 18:32:57 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clean_exit(t_env **env, char *line, int n)
{
	char	*err;

	err = "minishell: warning: here-document at\
	line 1 delimited by end-of-file\n";
	if (n == 1)
		ft_putstr_fd(err, 2);
	if (n == 2)
	{
		(void)line;
		ft_putstr_fd("maximum here-document count exceeded", 2);
		clean_all(env, 2, 0);
	}
	free(line);
	clean_all(env, 0, 0);
}

void	write_in_file(int fd, t_env **env, char *limiter)
{
	char	*line;
	char	*new_limiter;

	while (1)
	{
		line = readline(">");
		if (!line)
			ft_clean_exit(env, line, 1);
		new_limiter = rm_newline(limiter);
		if (ft_strccmp(new_limiter, line, ft_strlen(new_limiter)) == 0)
			ft_clean_exit(env, line, 0);
		gc_free_one(new_limiter);
		if (!*line && limiter[0] == '\n')
			ft_clean_exit(env, line, 0);
		if (!*line)
			continue ;
		helper_herdoc(line, fd, env);
		free(line);
	}
}

void	write_to_herdoc(int fd, t_env **env, char *limiter)
{
	char	*delimiter;

	gc_global->env = env;
	signal(SIGINT, handle_child_sig);
	if (*limiter == '\0')
		delimiter = ft_strjoin(limiter, "\n");
	else
	{
		delimiter = ft_strjoin(limiter, "\n");
	}
	write_in_file(fd, env, delimiter);
	close(fd);
}

int	ft_handle_herdoc(char *value, t_env **env, int *n)
{
	pid_t	pid;
	int		fd;
	int		status;

	pid = fork();
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0640);
	if (pid < 0)
		printf("fork failed.\n");
	else if (pid == 0)
		write_to_herdoc(fd, env, value);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 130)
		{
			*n = 1;
			update_exit_status(env, 130);
		}
		signal(SIGINT, handle_sig);
	}
	unlink("/tmp/heredoc");
	return (fd);
}

void	ft_herdoc(t_command **cmd, t_extra *ptr)
{
	t_command	*tmp;
	t_redi		*in;
	int			count;

	tmp = *cmd;
	count = 0;
	tmp->fd = -1;
	while (tmp)
	{
		in = tmp->in;
		tmp->fd = -1;
		while (in)
		{
			if (in->type == d_herdoc)
			{
				tmp->fd = ft_handle_herdoc(in->file, ptr->env, &ptr->flag_sig);
				count++;
				if (count > 16)
					ft_clean_exit(ptr->env, NULL, 2);
			}
			in = in->next;
		}
		tmp = tmp->next;
	}
}
