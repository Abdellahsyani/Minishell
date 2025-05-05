/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:06 by asyani            #+#    #+#             */
/*   Updated: 2025/05/01 13:53:29 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char		*dup;
	size_t		len;
	size_t		i;

	len = strlen(s1);
	i = 0;
	dup = gc_malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int main()
{
	char	*line;
	char	*type;
	t_token	*list = NULL;
	t_token *tmp = NULL;

	while (1)
	{
		line = readline("\033[1;32m minishell $ \033[0m");
		if (line)
			add_history(line);
		get_input(line, &list);
		tmp = list;
		while (tmp)
		{
			type = token_type(tmp);
			printf("%s[%d]: %s\n", type, tmp->type, tmp->content);
			tmp = tmp->next;
		}
		/*start_parsing(list);*/
		list = NULL;
	}
	return (0);
}
