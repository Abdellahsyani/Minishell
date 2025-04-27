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

#include "minishell.h"

t_token_type token_type(char *str)
{
    char type;
    if (!str)
        return;
    if (!strcmp(str, ">"))
        return (redir_output);
    if (!strcmp(str, "<"))
        return (redir_input);
    else if (!strcmp(str, "<<"))
        return (d_herdoc); 
    else if (!strcmp(str, ">>"))
        return (redir_o_app);
    else if (!strcmp(str, "|"))
        return (pipe);
    else
        return (word);  
}

