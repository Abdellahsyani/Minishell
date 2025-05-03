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

char	*token_type(char *str)
{
	char *type;

	if (!str)
		return (NULL);
	if (!ft_strcmp(str, ">"))
		type = ft_strdup("redir_output");
	else if (!ft_strcmp(str, "<"))
		type = ft_strdup("redir_input");
	else if (!ft_strcmp(str, "<<"))
		type = ft_strdup("d_herdoc"); 
	else if (!ft_strcmp(str, ">>"))
		type = ft_strdup("redir_o_app");
	else if (!ft_strcmp(str, "|"))
		type = ft_strdup("pipe_line");
	else
		type = ft_strdup("word");  
	return (type);
}
