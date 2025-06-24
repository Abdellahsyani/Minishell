/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:09 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/24 20:43:07 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_regular_executable(char *path)
{
	struct stat	sb;

	if (access(path, X_OK) != 0)
		return (0);
	if (stat(path, &sb) != 0)
		return (0);
	if (S_ISDIR(sb.st_mode) && slash(path))
		return (2);
	if (S_ISREG(sb.st_mode) && slash(path))
		return (1);
	else
		return (0);
}

char	*find_path(char *cmd, t_env **env)
{
	int		i;
	t_env	*cur;
	char	**paths;
	char	*ppth;
	char	*path;

	i = -1;
	if (is_regular_executable(cmd))
		return (cmd);
	cur = *env;
	while (ft_strncmp(cur->key, "PATH", 4))
		cur = cur->next;
	paths = ft_split(cur->value, ':');
	while (paths[++i])
	{
		ppth = ft_strjoin(paths[i], "/");
		path = ft_strjoin(ppth, cmd);
		gc_free_one(ppth);
		if (!access(path, X_OK))
		{
			gc_free_one(paths[i]);
			return (path);
		}
	}
	return (NULL);
}

int	**allocate_tube(int size)
{
	int	**tube;
	int	i;

	i = 0;
	if (size < 0)
		return (0);
	tube = gc_malloc(sizeof(int *) * size);
	if (!tube)
		return (0);
	while (i < size)
	{
		tube[i] = gc_malloc(sizeof(int) * 2);
		if (!tube[i])
			return (0);
		i++;
	}
	return (tube);
}
