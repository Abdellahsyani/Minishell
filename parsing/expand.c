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
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*get_var(char *str)
{
	char	*var;
	int	i;
	int	start;
	int	len;

	i = 0;
	len = 0;
	start = 0;
	var = NULL;
	start = i;
	while (ft_isalpha(str[i]) || str[i] == '_')
	{
		if (str[i] == ' ' || str[i] == '"')
			break;
		i++;
	}
	len = i;
	var = ft_strlcpy(var, str, len, start);
	printf("var: %s\n", var);
	return (var);
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
			int i = 0;
			while (list && list->content[i])
			{
				if (list->content[i] == '\'')
					single_qoute(&);
				if (list->content[i] == '"')
					double_quote();
				if (list->content[i] == '$')
					get_var(&list->content[i + 1]);
				i++;
			}
			if ((extract_var(list->content)) == 1)
			{
				int	i = 0;
				int	j = 0;
				int	len = 0;
				int	skip = 0;
				char *var1 = NULL;

				while (list && list->content[i])
				{
					if (list->content[i] == '\'' || list->content[i] == '"')
						skip++;
					i++;
				}
				i = 0;
				len = ft_strlen(list->content);
				var1 = gc_malloc(sizeof(char) * ((len - skip) + 1));
				while (list && list->content[i])
				{
					if (list->content[i] == '\'' || list->content[i] == '"')
						i++;
					else
					{
						var1[j] = list->content[i];
						i++;
						j++;
					}
				}
				var1[i] = '\0';
				printf("%s", var1);
			}
			else
			{
				/*printf(" %s", list->content);*/
				/*int	i = 0;* /
				/*while (list->content[i])*/
				/*{*/
				/*	if (list->content[i] == ' ')*/
				/*		i++;*/
				/*}*/
			}
			/*if (list->content[0] == '$')*/
			/*{*/
			/*	if (getenv(list->content + 1) == NULL)*/
			/*		var = ft_strdup("");*/
			/*	else*/
			/*		var = ft_strdup(getenv(list->content + 1));*/
			/*	printf("%s ", var);*/
			/*}*/
			/*else*/
			/*	printf("%s ", list->content);*/
		}
		list = list->next;
	}
	printf("\n");
}
