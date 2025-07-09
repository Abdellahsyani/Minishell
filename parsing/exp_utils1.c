/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:45:22 by asyani            #+#    #+#             */
/*   Updated: 2025/06/24 18:40:30 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_space_size(char *str, int temp_i)
{
	int	result_len;
	int	in_whitespace;

	in_whitespace = 1;
	result_len = 0;
	while (str[temp_i])
	{
		if (str[temp_i] == ' ' || str[temp_i] == '\t')
		{
			if (!in_whitespace && str[temp_i + 1] && str[temp_i + 1] != ' '
				&& str[temp_i + 1] != '\t')
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

static char	*fill_nonspace(char *str, int i, char *result, int j)
{
	int	in_whitespace;

	in_whitespace = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			if (!in_whitespace)
				count_space(str, result, &i, &j);
			in_whitespace = 1;
		}
		else
		{
			result[j++] = str[i];
			in_whitespace = 0;
		}
		i++;
	}
	return (result[j] = '\0', result);
}

static char	*norm_whitespace(char *str, char *var_quote, char *get_last, int i)
{
	char	*result;
	int		result_len;
	int		temp_i;

	result_len = 0;
	result = NULL;
	if (*str)
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		temp_i = i;
		result_len = get_space_size(str, temp_i);
		if (str && str[ft_strlen(str) - 1] == ' ' && get_last)
			result_len += 1;
		result = gc_malloc(sizeof(char) * (result_len + 2));
		result = fill_nonspace(str, i, result, 0);
		if (var_quote)
			result = ft_strjoin(result, var_quote);
		if (str[ft_strlen(str) - 1] == ' ' && get_last)
			result = ft_strjoin(result, " ");
	}
	if (get_last)
		result = ft_strjoin(result, get_last);
	return (result);
}

static char	*get_allstr(char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i])
		i++;
	value = ft_substr(str, 0, i);
	return (value);
}

char	*get_var(char *str, t_env **env, int i)
{
	int		len;
	char	*var_name;
	char	*var_value;
	char	*var_quote;
	char	*get_last;

	var_quote = NULL;
	get_last = NULL;
	if (str[i] == '?')
		return (get_status(&str[i], env, 0, 0));
	if (str[0] == '$' && (str[1] == '\0' || !ft_isalnum(str[1])))
		return (ft_strdup("$"));
	i = get_all_var(str, &i);
	if ((str[i] && str[i] == '"' && str[i + 1]))
		var_quote = double_quote(&str[i], env);
	else if (!ft_isalpha(str[i]))
		get_last = ft_strdup(get_allstr(&str[i]));
	len = i - 1;
	var_name = ft_strlcpy(NULL, str, len, 1);
	var_value = ft_get(env, var_name);
	if (!var_value)
		var_value = ft_strdup("");
	return (norm_whitespace(var_value, var_quote, get_last, 0));
}
