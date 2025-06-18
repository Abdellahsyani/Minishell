/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:51:37 by asyani            #+#    #+#             */
/*   Updated: 2025/06/16 09:48:48 by abdo             ###   ########.fr       */
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
	char	*exp;
	char	*last;
	int	i;
	int	j;

	i = 0;
	j = 0;
	int len = ft_strlen(str);
	last = gc_malloc(sizeof(char) * len);
	if (!last)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '?')
			exp = ft_strdup("?");
		else
		{
			last[j] = str[i];
			j++;
		}
		i++;
	}
	last[j] = '\0';
	var = ft_strdup(ft_get(env, exp));
	if (last)
		var = ft_strjoin(var, last);
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
		result = ft_strjoin(result, get_last);
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
	int i;
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
	if (*str == '$' && !ft_isalpha(str[i + 1]))
		return ("$");
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
	while (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?')
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

char	*single_quote(char *content)
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
	if (!var)
		return (NULL);
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

void	count_dollar(t_hold *var, char *content)
{
	var->coun = 0;
	var->var = NULL;
	var->i = 0;
	var->len1 = 0;
	var->len = 0;
	var->var1 = NULL;
	while (content[var->i])
	{
		if (content[var->i] == '$')
			var->coun++;
		var->i++;
	}
	var->env = gc_malloc(sizeof(char *) * (var->coun + 1));
	if (!var->env)
		return ;
	var->env[0] = NULL;
	var->env_var = gc_malloc(sizeof(char *) * (var->coun + 1));
	if (!var->env_var)
		return ;
	var->env_var[0] = NULL;
}

void	let_var_ready(t_hold *var, char *content, t_env **env_t)
{
	var->counts = 0;
	var->count = 0;
	var->i = 0;
	var->exp = NULL;
	var->get_v = NULL;
	while (content[var->i])
	{
		if (content[var->i] == '$')
		{
			var->get_v = get_var1(&content[var->i]);
			var->env_var[var->counts] = ft_strdup(var->get_v);
			var->exp = ft_get(env_t, var->get_v);
			if (var->exp)
				var->env[var->counts] = ft_strdup(var->exp);
			else
				var->env[var->counts] = ft_strdup("");
			var->counts++;
		}
		if (content[var->i] == '"')
		{
			var->i++;
			continue;
		}
		var->i++;
		var->count++;
	}
	var->env[var->counts] = NULL;
	var->env_var[var->counts] = NULL;
}

void	ft_get_var(t_hold *var, char *content)
{
	var->i = 0;
	while (var->env[var->i])
	{
		var->len1 += ft_strlen(var->env[var->i]);
		var->i++;
	}
	var->i = 0;
	while (var->env_var[var->i])
	{
		var->len += ft_strlen(var->env_var[var->i]);
		var->i++;
	}
	var->var = gc_malloc(sizeof(char) * (var->count + 1));
	if (!var->var)
		return ;
	var->var = stcopy(var->var, content, '"');
	var->i = 0;
	var->k = 0;
	var->j = 0;
	var->var1 = NULL;
	var->size_all = 0;
	var->size_all = var->count + var->len1 - (var->len + var->coun);
	var->var1 = gc_malloc(sizeof(char) * (var->size_all + 1));
	if (!var->var1)
		return ;
}

char	*double_quote(char *content, t_env **env_t)
{
	t_hold	var;
	int	s;
	int	c;

	var.i = 0;
	while (content[var.i])
	{
		if (content[var.i] == '$' && (!ft_isalpha(content[var.i + 1])
			|| content[var.i+1] != '_'))
			printf("$");
		var.i++;
	}
	count_dollar(&var, content);
	let_var_ready(&var, content, env_t);
	ft_get_var(&var, content);
	while (var.var[var.i])
	{
		if (var.var[var.i] != '$')
			var.var1[var.j] = var.var[var.i];
		else
		{
			var.var1[var.j] = '\0';
			var.var1 = ft_strjoins(var.var1, var.env[var.k]);
			s = ft_strlen(var.env[var.k]);
			c = ft_strlen(var.env_var[var.k]);
			var.k++;
			var.i += c + 1;
			var.j += s;
			continue;
		}
		var.j++;
		var.i++;
	}
	var.var1[var.j] = '\0';
	free_2d(var.env);
	free_2d(var.env_var);
	return (var.var1);
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
		if (var[i] == '\'')
		{
			quote = single_quote(&var[i]);
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
		if (cmd->argv_t[0][0] == '$' && cmd->argv_t[0][1] == '\0')
		{
			printf(" command not found\n");
			return (0);
		}
		var = get_var(cmd->argv_t[0], env);
		if(!var)
			return (0);
		spl = ft_split(var, ' ');
		i = 0;
		while (spl[i])
			i++;
		cmd->argv = gc_malloc(sizeof(char *) * (i + 1));
		i = 0;
		j = 0;
		while (spl[i])
		{
			cmd->argv[j] = ft_strdup(spl[i]);
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
				cmd->argv[i] = single_quote(cmd->argv_t[i]);
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
