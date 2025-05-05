/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:04:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/27 16:04:57 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*token_type(t_token *list)
{
	char *type;

	if (!list->content)
		return (NULL);
	if (!ft_strcmp(list->content, ">"))
	{
		list->type = redir_output;
		type = ft_strdup("redir_output");
	}
	else if (!ft_strcmp(list->content, "<"))
	{
		list->type = redir_input;
		type = ft_strdup("redir_input");
	}
	else if (!ft_strcmp(list->content, "<<"))
	{
		list->type = d_herdoc;
		type = ft_strdup("d_herdoc"); 
	}
	else if (!ft_strcmp(list->content, ">>"))
	{
		list->type = redir_o_app;
		type = ft_strdup("redir_o_app");
	}
	else if (!ft_strcmp(list->content, "|"))
	{
		list->type = pipe_line;
		type = ft_strdup("pipe_line");
	}
	else
	{
		list->type = word;
		type = ft_strdup("word");  
	}
	return (type);
}
