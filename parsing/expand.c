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

char *ft_get(t_env **env, char *key)
{
	t_env *tmp;
	tmp = *env;
    while (tmp)
    {
        if (!ft_strcmp((tmp)->key, key))
            return (tmp->value);
        (tmp) = (tmp)->next;
    }
    return (NULL);
}

char	*get_var(char *str, t_env **env)
{
	char	*var;
	int	i;
	int	start;
	int	len;
	char	*var1;

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
	var1 = ft_get(env, var);
	if (!var1)
		var1 = ft_strdup("");
	/*printf("\nvar_$: %s\n", var1);*/
	return (var1);
}

char	*get_var1(char *str)
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
	/*printf("\nvar1_$: %s\n", var);*/
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
	/*printf("var_': %s\n", var);*/
	return (var);
}

char	*double_quote(char *content, t_env **env_t)
{
	int	i;
	char	*var = NULL;
	int	count = 0;
	char	*exp = NULL;
	char	*get_v = NULL;
	char	*var1 = NULL;
	int	len = 0;
	int	len1;
	char	**env;
	char	**env_var;
	int	coun;
	int	*track_size = NULL;
	int	*track_s = NULL;

	i = 0;
	len1 = 0;
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
	if (!env)
		return NULL;
	env[0] = NULL;
	env_var = gc_malloc(sizeof(char *) * (coun + 1));
	if (!env_var)
		return NULL;
	env_var[0] = NULL;
	int counts = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			get_v = get_var1(&content[i]);
			env_var[counts] = ft_strdup(get_v);
			exp = ft_get(env_t, get_v);
			if (exp)
				env[counts] = ft_strdup(exp);
			else
				env[counts] = ft_strdup("");
			counts++;
		}
		if (content[i] == '"')
		{
			i++;
			continue;
		}
		i++;
		count++;
	}
	env[counts] = NULL;
	env_var[counts] = NULL;
	/*printf("\n------------\n");*/
	/*printf("env-->%s\n", env[0]);*/
	/*printf("env-->%s\n", env[1]);*/
	/*printf("env_var-->%s\n", env_var[0]);*/
	/*printf("env_var-->%s\n", env_var[1]);*/
	/*printf("count--> %d\n", count);*/
	/*printf("\n------------\n");*/
	i = 0;
	track_size = gc_malloc(sizeof(int) * (coun + 1));
	if (!track_size)
		return (NULL);
	track_size[0] = '\0';
	track_s = gc_malloc(sizeof(int) * (coun + 1));
	if (!track_s)
		return (NULL);
	track_s[0] = '\0';
	while (env[i])
	{
		track_size[i] = ft_strlen(env[i]);
		i++;
	}
	i = 0;
	while (env_var[i])
	{
		track_s[i] = ft_strlen(env_var[i]);
		i++;
	}
	i = 0;
	while (track_s[i])
	{
		len1 += track_s[i];
		i++;
	}
	i = 0;
	while (track_size[i])
	{
		len += track_size[i];
		i++;
	}

	var = gc_malloc(sizeof(char) * (count + 1));
	var = stcopy(var, content, '"');
	/*printf("\nvar--> %s\n", var);*/
	i = 0;
	int k = 0;
	int	j = 0;
	var1 = gc_malloc(sizeof(char) * ((count + len - len1 + 1) - coun));
	if (!var1)
		return (NULL);
	var1[0] = '\0';
	while (var[i])
	{
		if (var[i] != '$')
			var1[j] = var[i];
		else
		{
			var1[j] = '\0';
			var1 = ft_strjoin(var1, env[k]);
			int s = ft_strlen(env[k]);
			int c = ft_strlen(env_var[k]);
			k++;
			i += c + 1;
			j += s;
			continue;
		}
		j++;
		i++;
	}
	var1[j] = '\0';
	/*printf("var_\": %s\n", var1);*/
	return (var1);
}

char	*copy_var(char *content)
{
	int	i;
	int	len;
	char	*var = NULL;
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
	/*printf("var_all: %s", var);*/
	return (var);
}


void	expand_var(t_token *list, t_command *cmd, t_env **env)
{
	int	i;
	char	*all_cmd;
	int	count;
	(void)list;

	all_cmd = NULL;
	while (cmd)
	{
		count = 0;
		while (cmd && cmd->argv_t[count])
			count++;
		cmd->argv = gc_malloc(sizeof(char *) * (count + 1));
		if (!cmd->argv)
			return ;
		i = 0;
		while (cmd->argv_t[i])
		{
			if (cmd->argv_t[i][0] == '\'')
				cmd->argv[i] = ft_strdup(single_qoute(cmd->argv_t[i]));
			else if (cmd->argv_t[i][0] == '"')
				cmd->argv[i] = ft_strdup(double_quote(cmd->argv_t[i], env));
			else if (cmd->argv_t[i][0] == '$')
				cmd->argv[i] = ft_strdup(get_var(cmd->argv_t[i], env));
			else
				cmd->argv[i] = ft_strdup(copy_var(cmd->argv_t[i]));
			all_cmd = ft_strjoin(all_cmd, cmd->argv[i]);
			if (cmd->argv_t[i + 1] != NULL && ft_isalpha(cmd->argv[i][0]))
				all_cmd = ft_strjoin(all_cmd, " ");
			i++;
		}
		cmd->argv[i] = NULL;
		cmd = cmd->next;
	}
	/*printf("\n---all_cmd---: %s\n", all_cmd);*/
}
