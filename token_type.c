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

#include "minishell.h"

char* token_type(char *str)
{
    char type;
    if (!str)
        return;
    if (!strcmp(str, ">"))
        type = redir_output;
    if (!strcmp(str, "<"))
        type = redir_input;
    else if (!strcmp(str, "<<"))
        type = d_herdoc; 
    else if (!strcmp(str, ">>"))
        type = redir_o_app;
    else if (!strcmp(str, "|"))
        type = pipe;
    else
        type = word;
    return (type);  
}
