/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_st.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:08:28 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/12 11:15:48 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_exit_status(t_env **env,int status)
{
    char *value;
    
    value = ft_itoa(status);
    set_new_env("?", value, env);
}