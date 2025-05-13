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

static	char	*helper(char *concat, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		concat[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		concat[i + j] = s2[j];
		j++;
	}
	concat[i + j] = '\0';
	return (concat);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*concat;
	int		s1_size;
	int		s2_size;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	concat = gc_malloc(sizeof(char) * (s1_size + s2_size) + 1);
	if (!concat)
		return (NULL);
	helper(concat, s1, s2);
	return (concat);
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

	i = 1;
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
	len = i - 1;
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
	int	j;
	char	*var;
	int	count = 0;
	char	*exp;
	char	*get_v;
	char	*var1;
	int	len;
	int	len1;
	char	**env;
	int	coun;
	int	*track_size;

	i = 0;
	j = 0;
	coun = 0;
	var = NULL;
	while (content[i])
	{
		if (content[i] == '$')
			coun++;
		i++;
	}
	i = 0;
	env = gc_malloc(sizeof(char *) * (coun + 1));
	env[0] = NULL;
	coun = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			get_v = get_var(&content[i]);
			exp = getenv(get_v);
			if (exp)
				env[coun] = ft_strdup(exp);
			else
				env[coun] = ft_strdup("");
			coun++;
		}
		if (content[i] == '"')
		{
			i++;
			continue;
		}
		i++;
		count++;
	}
	printf("\n------------\n");
	printf("\nvar-->%s\n", env[0]);
	printf("\nvar-->%s\n", env[1]);
	printf("\n------------\n");
	i = 0;
	track_size = gc_malloc(sizeof(int) * 2);
	while (env[i])
	{
		track_size[i] = ft_strlen(env[i]);
		i++;
	}
	i = 0;
	while (track_size[i])
	{
		len += track_size[i];
		i++;
	}

	printf("len: -->%d\n", len);
	var = gc_malloc(sizeof(char) * (count + 1));
	var = stcopy(var, content, '"');
	printf("\nvar-->%s\n", var);
	len1 = ft_strlen(get_v);
	i = 0;
	int k = 0;
	var1 = gc_malloc(sizeof(char) * (count + len - 8 + 1));
	while (var[i])
	{
		if (var[i] != '$')
		{
			var1[j] = var[i];
		}
		else
		{
			var1 = ft_strjoin(var1, env[k]);
			k++;
			i += len1 + 1;
			j += len;
			continue;
		}
		j++;
		i++;
	}
	printf("var_\": %s\n", var1);
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
	char	*all_cmd;

	all_cmd = NULL;
	i = 0;
	while (cmd->argv[i])
	{
		/*printf("argv: %s[%d]\n", cmd->argv[i], i);*/
		if (cmd->argv[i][0] == '\'')
			var = single_qoute(cmd->argv[i]);
		else if (cmd->argv[i][0] == '"')
			var = double_quote(cmd->argv[i]);
		else if (cmd->argv[i][0] == '$')
			var = getenv(get_var(cmd->argv[i]));
		else
			var = copy_var(cmd->argv[i]);
		all_cmd = ft_strjoin(all_cmd, var);
		i++;
	}
	printf("\n---all_cmd---: %s\n", all_cmd);
	printf("\n");
}

