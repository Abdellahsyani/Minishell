/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:01:58 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/31 15:57:33 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    handle_sig(int signum)
{
    (void)signum;
    
    rl_replace_line("", 0);
    rl_on_new_line();
    printf("\n");
    rl_redisplay();
}
void handle_child_sig(int signum)
{
    (void)signum;
    exit(130);
}