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

char	*stcopy(char *var, char *content, char del)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == del)
		{
			i++;
			continue;
		}
		var[count] = content[i];
		count++;
		i++;
	}
	var[count] = '\0';
	return (var);
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
	printf("var_$: %s\n", var);
	return (var);
}

char	*single_qoute(char *content)
{
	int	i;
	int	count;
	char	*var;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'')
		{
			i++;
			continue;
		}
		i++;
		count++;
	}
	var = gc_malloc(sizeof(char) * (count + 1));
	var = stcopy(var, content, '\'');
	printf("var_': %s\n", var);
	return (var);
}


char	*double_quote(char *content)
{
	int	i;
	char	*var;
	int count = 0;

	i = 0;
	var = NULL;
	while (content[i])
	{
		if (content[i] == '"')
		{
			i++;
			continue;
		}
		i++;
		count++;
	}
	var = gc_malloc(sizeof(char) * count + 1);
	var = stcopy(var, content, '"');
	printf("var_\": %s\n", var);
	return (var);
}


char	*copy_var(char *content)
{
	int	i;
	int	len;
	char	*var;
	int	start;

	i = 0;
	start = i;
	while (content[i])
	{
		if (content[i] == ' ')
			break ;
		i++;
	}
	len = i;
	var = ft_strlcpy(var, content, len, start);
	printf("var_all: %s", var);
	return (var);
}

void	expand_var(t_token *list, t_command *cmd)
{
	int	i;
	char	*var;

	i = 0;
	while (cmd->argv[i])
	{
		if (list->content[0] == '\'')
			var = single_qoute(cmd->argv[i]);
		else if (list->content[0] == '"')
			var = double_quote(cmd->argv[i]);
		else if (list->content[i] == '$')
			var = get_var(&list->content[i + 1]);
		/*else*/
		/*	var = copy_var(&list->content[i]);*/
		/*if ((extract_var(list->content)) == 1)*/
		/*{*/
		/*	int	i = 0;*/
		/*	int	j = 0;*/
		/*	int	len = 0;*/
		/*	int	skip = 0;*/
		/*	char *var1 = NULL;*/
		/**/
		/*	while (list && list->content[i])*/
		/*	{*/
		/*		if (list->content[i] == '\'' || list->content[i] == '"')*/
		/*			skip++;*/
		/*		i++;*/
		/*	}*/
		/*	i = 0;*/
		/*	len = ft_strlen(list->content);*/
		/*	var1 = gc_malloc(sizeof(char) * ((len - skip) + 1));*/
		/*	while (list && list->content[i])*/
		/*	{*/
		/*		if (list->content[i] == '\'' || list->content[i] == '"')*/
		/*			i++;*/
		/*		else*/
		/*		{*/
		/*			var1[j] = list->content[i];*/
		/*			i++;*/
		/*			j++;*/
		/*		}*/
		/*	}*/
		/*	var1[i] = '\0';*/
		/*	printf("%s", var1);*/
		/*}*/
		/*else*/
		/*{*/
		/*	printf(" %s", list->content);*/
		/*	int	i = 0;*/
		/*	while (list->content[i])*/
		/*	{*/
		/*		if (list->content[i] == ' ')*/
		/*			i++;*/
		/*	}*/
		/*}*/
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
		i++;
	}
	printf("\n");
}
