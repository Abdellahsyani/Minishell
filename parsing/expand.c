/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:51:37 by asyani            #+#    #+#             */
/*   Updated: 2025/06/04 17:58:42 by abhimi           ###   ########.fr       */
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

char	*get_status(char *str, t_env **env)
{
	char	*var;

	var = ft_strdup(ft_get(env, str));
	return (var);
}

int	get_space_size(char *str, int temp_i)
{
	int	result_len;
	int in_whitespace;

	in_whitespace = 1;
	result_len = 0;
	while (str[temp_i])
	{
		if (str[temp_i] == ' ' || str[temp_i] == '\t')
		{
			if (!in_whitespace && str[temp_i + 1] && 
				str[temp_i + 1] != ' ' && str[temp_i + 1] != '\t')
				result_len++;
			in_whitespace = 0;
		}
		else
	{
			result_len++;
			in_whitespace = 1;
		}
		temp_i++;
	}
	return (result_len);
}

char	*fill_nonspace(char *str, int i, char *result)
{
	int in_whitespace;
	int j;

	j = 0;
	in_whitespace = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			if (!in_whitespace)
			{
				int k = i;
				while (str[k] && (str[k] == ' ' || str[k] == '\t'))
					k++;
				if (str[k])
					result[j++] = ' ';
			}
			in_whitespace = 1;
		}
		else
		{
			result[j++] = str[i];
			in_whitespace = 0;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*norm_whitespace(char *str, char *var_quote, char *get_last)
{
	char *result;
	int i;
	int result_len;
	int temp_i;

	i = 0;
	result_len = 0;
	if (!*str)
		return (NULL);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	temp_i = i;
	result_len = get_space_size(str, temp_i);
	if (str && str[ft_strlen(str) - 1] == ' ' && get_last)
		result_len += 1;
	result = gc_malloc(sizeof(char) * result_len + 1);
	if (!result)
		return NULL;
	result = fill_nonspace(str, i, result);
	if (var_quote)
		result = ft_strjoin(result, var_quote);
	if (str[ft_strlen(str) - 1] == ' ' && get_last)
		result = ft_strjoin(result, " ");
	if (get_last)
		ft_strjoin(result, get_last);
	return (result);
}

char *get_allstr(char *str)
{
	int	i;
	char	*value;

	i = 0;
	while (str[i])
		i++;
	value = ft_substr(str, 0, i);
	return value;
}

char *get_var(char *str, t_env **env)
{
	int i = 1;
	int start;
	int len;
	char *var_name;
	char *var_value;
	char	*var_quote;
	char	*get_last;

	i = 1;
	start = i;
	var_quote = NULL;
	get_last = NULL;
	if (str[i] == '?')
		return (get_status(&str[i], env));
	while (ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i]))
		i++;
	if ((str[i] && str[i] == '"' && str[i + 1] == '$') || (str[i] && ft_isalpha(str[i + 1])))
		var_quote = double_quote(&str[i], env);
	else if (!ft_isalpha(str[i]))
		get_last = ft_strdup(get_allstr(&str[i]));
	len = i - start;
	var_name = ft_strlcpy(NULL, str, len, start);
	var_value = ft_get(env, var_name);
	if (!var_value)
		var_value = ft_strdup("");
	return (norm_whitespace(var_value, var_quote, get_last));
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
	count = 0;
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

char	*ft_strjoins(char *s1, char *s2)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	return (s1);
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
	i = 0;
	track_size = gc_malloc(sizeof(int) * coun);
	if (!track_size)
		return (NULL);
	track_s = gc_malloc(sizeof(int) * coun);
	if (!track_s)
		return (NULL);
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
	while (i < coun)
	{
		len1 += track_s[i];
		i++;
	}
	i = 0;
	while (i < coun)
	{
		len += track_size[i];
		i++;
	}
	var = gc_malloc(sizeof(char) * (count + 1));
	if (!var)
		return NULL;
	var = stcopy(var, content, '"');
	i = 0;
	int k = 0;
	int	j = 0;
	int size_all = count + len - (len1 + coun);
	var1 = gc_malloc(sizeof(char) * size_all + 1);
	if (!var1)
		return (NULL);
	while (var[i])
	{
		if (var[i] != '$')
		{
			var1[j] = var[i];
		}
		else
		{
			var1[j] = '\0';
			var1 = ft_strjoins(var1, env[k]);
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
	free_2d(env);
	free_2d(env_var);
	gc_free_one(track_size);
	gc_free_one(track_s);
	return (var1);
}

char	*when_quote(char *var, char *quote, int i)
{
	char	*copy;

	copy = NULL;
	copy = ft_strlcpy(copy, var, i, 0);
	copy = ft_strjoin(copy, quote);
	/*printf("copy_all: %s\n", copy);*/
	return (copy);
}

char	*copy_var(char *content, t_env **env)
{
	int	i;
	int	len;
	char	*var;
	int	start;
	char	*quote;

	i = 0;
	start = i;
	var = NULL;
	quote = NULL;
	while (content[i])
		i++;
	len = i;
	var = ft_strlcpy(var, content, len, start);
	i = 0;
	while (var[i])
	{
		if (var[i] == '"')
		{
			quote = double_quote(&var[i], env);
			break;
		}
		i++;
	}
	if (quote)
		return (when_quote(var, quote, i));
	/*printf("var_all: %s\n", var);*/
	return (var);
}

int	h_export(t_command *cmd, t_env **env)
{
	char	*var;
	char	**spl;
	int	i;
	int	j;
	spl = NULL;
	if (cmd->argv_t[0][0] == '"' && cmd->argv_t[0][1] == '$')
	{
		printf("bash: %s: command not found\n", get_var(&cmd->argv_t[0][1], env));
		return (0);
	}
	if (cmd->argv_t[0][0] == '$')
	{
		var = get_var(cmd->argv_t[0], env);
		spl = ft_split(var, ' ');
		i = 0;
		while (spl[i])
			i++;
		cmd->argv = gc_malloc(sizeof(char *) * (i + 1));
		i = 0;
		j = 0;
		while (spl[i])
		{
			cmd->argv[j] = spl[i];
			i++;
			j++;
		}
		cmd->argv[j] = NULL;
	}
	free_2d(spl);
	free_2d(cmd->argv_t);
	return (1);
}

void	expand_var(t_command *cmd, t_env **env)
{
	int	i;
	int	count;

	if (!cmd->argv_t)
		return ;
	while (cmd)
	{
		count = 0;
		while (cmd && cmd->argv_t[count])
			count++;
		cmd->argv = gc_malloc(sizeof(char *) * (count + 1));
		if (!cmd->argv)
			return ;
		i = 0;
		if (cmd->argv_t[0][0] == '$' || (cmd->argv_t[0][0] == '"' && cmd->argv_t[0][1] == '$'))
		{
			h_export(cmd, env);
			break;
		}
		while (cmd->argv_t[i])
		{
			if (cmd->argv_t[i][0] == '\'')
				cmd->argv[i] = single_qoute(cmd->argv_t[i]);
			else if (cmd->argv_t[i][0] == '"')
				cmd->argv[i] = double_quote(cmd->argv_t[i], env);
			else if (cmd->argv_t[i][0] == '$')
				cmd->argv[i] = get_var(cmd->argv_t[i], env);
			else
				cmd->argv[i] = copy_var(cmd->argv_t[i], env);
			i++;
		}
		cmd->argv[i] = NULL;
		cmd = cmd->next;
	}
}
