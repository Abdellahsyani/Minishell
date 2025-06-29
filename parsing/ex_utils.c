/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:40:46 by asyani            #+#    #+#             */
/*   Updated: 2025/06/21 18:42:37 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	count_dollar(t_hold *var, char *content)
{
	var->coun = 0;
	var->var = NULL;
	var->len1 = 0;
	var->len = 0;
	var->var1 = NULL;
	var->exp = NULL;
	var->get_v = NULL;
	var->counts = 0;
	var->count = 0;
	while (content[var->i])
	{
		if (content[var->i] == '$' && (ft_isalnum(content[var->i + 1])
				|| content[var->i + 1] == '?' || content[var->i + 1] == '_'))
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
	var->i = 0;
}

static void	let_var_ready(t_hold *var, char *content, t_env **env_t)
{
	while (content[var->i])
	{
		if (content[var->i] == '$' && (ft_isalnum(content[var->i + 1])
				|| content[var->i + 1] == '?' || content[var->i + 1] == '_'))
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
			g_global->count_double += 1;
			var->i++;
			continue ;
		}
		var->i++;
		var->count++;
	}
	var->env[var->counts] = NULL;
	var->env_var[var->counts] = NULL;
}

static void	ft_get_var(t_hold *var, char *content)
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
	var->var = stcopy(var->var, content);
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

static void	fill_var(t_hold *var)
{
	int	s;
	int	c;

	while (var->var[var->i])
	{
		if (var->var[var->i] != '$')
			var->var1[var->j] = var->var[var->i];
		else if (var->var[var->i] == '$' && (ft_isalnum(var->var[var->i + 1])
				|| var->var[var->i + 1] == '?' || var->var[var->i + 1] == '_'))
		{
			var->var1[var->j] = '\0';
			var->var1 = ft_strjoins(var->var1, var->env[var->k]);
			s = ft_strlen(var->env[var->k]);
			c = ft_strlen(var->env_var[var->k]);
			var->k++;
			var->i += c + 1;
			var->j += s;
			continue ;
		}
		else
			var->var1[var->j] = var->var[var->i];
		var->j++;
		var->i++;
	}
	var->var1[var->j] = '\0';
}

char	*double_quote(char *content, t_env **env_t)
{
	t_hold	var;

	var.i = 0;
	while (content[var.i])
	{
		if (ft_isalnum(content[var.i + 1]) || content[var.i + 1] == '?'
			|| content[var.i + 1] == '_')
			break ;
		if (content[var.i] == '$' && (content[var.i + 1] == '\0'
				|| content[var.i + 1] == '$'))
			write(1, "$", 1);
		var.i++;
	}
	var.i = 0;
	count_dollar(&var, content);
	let_var_ready(&var, content, env_t);
	ft_get_var(&var, content);
	fill_var(&var);
	free_2d(var.env);
	free_2d(var.env_var);
	return (var.var1);
}
