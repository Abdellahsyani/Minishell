/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:51:37 by asyani            #+#    #+#             */
/*   Updated: 2025/05/09 10:51:52 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	extract_var(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			return (1);
		if (str[i] == '"')
			return (2);
		i++;
	}
	return (0);
}


void	expand_var(t_token *list, t_command *cmd)
{
	int	i;
	char	*var;

	i = 0;
	while (list)
	{
		if (list->type == word)
		{
			printf("%s\n", list->content);
			printf("-----------------------\n");
			if ((extract_var(list->content)) == 1)
			{
				int	i = 0;
				int	j = 0;
				int	len = 0;
				char *var1;

				len = strlen(list->content);
				printf("%d\n", len);
				var1 = malloc(sizeof(char) * (len - 1));
				while (list && list->content[i])
				{
					if (list->content[i] == '\'')
						i++;
					else
					{
						var1[j] = list->content[i];
						i++;
						j++;
					}
				}
				var1[i] = '\0';
				printf("%s\n", var1);
				printf("-----------------------\n");
			}
			if (list->content[0] == '$')
			{
				if (getenv(list->content + 1) == NULL)
					var = ft_strdup("");
				else
					var = ft_strdup(getenv(list->content + 1));
				printf("this: %s\n", var);
			}
			if ((extract_var(list->content)) == 2)
			{
				int	i = 0;
				int	j = 0;
				int	len = 0;
				char *var1;

				len = strlen(list->content);
				printf("%d\n", len);
				var1 = malloc(sizeof(char) * (len - 1));
				while (list && list->content[i])
				{
					if (list->content[i] == '"')
						i++;
					else
					{
						if (list->content[i] == '$')
						{
							i++;
							while (list->content[i] != ' ' && list->content[i] != '"' && list->content[i] != '\0')
							{
								var1[j] = list->content[i];
								i++;
								j++;
							}
							var = ft_strdup(getenv(var1));
							printf("this var: %s\n", var);
						}
						else
						{
							var1[j] = list->content[i];
							i++;
							j++;
						}
					}
				}
				var1[i] = '\0';
				printf("%s\n", var1);
				printf("-----------------------\n");
			}
		}
		list = list->next;
	}
}
