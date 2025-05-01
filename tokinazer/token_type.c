/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:04:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/26 11:45:40 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*token_type(char *str)
{
	char	*type;

	if (!str)
		return (NULL);
	if (!ft_strcmp(str, ">"))
		type = redir_output;
	else if (!ft_strcmp(str, "<"))
		type = redir_input;
	else if (!ft_strcmp(str, "<<"))
		type = d_herdoc; 
	else if (!ft_strcmp(str, ">>"))
		type = redir_o_app;
	else if (!ft_strcmp(str, "|"))
		type = pipe_line;
	else
		type = word;
	return (type);  
}
