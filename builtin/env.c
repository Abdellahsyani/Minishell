/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:tokinazer/token_type.c
/*   Created: 2025/04/26 11:04:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/27 16:04:57 by abdo             ###   ########.fr       */
========
/*   Created: 2025/04/29 14:51:44 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/06 13:50:58 by abhimi           ###   ########.fr       */
>>>>>>>> builtin:builtin/env.c
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<<< HEAD:tokinazer/token_type.c
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

========
int ft_env(t_env **env)
{
    t_env *tmp;
    
    tmp = *env;
    if (!tmp)
        return (1);
    while(tmp)
    {
        printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
    return (0);
}
// int main(int ac, char **args, char **env)
// {
//     (void)ac;
//     (void)args;
//     t_env **envp;

//     envp = get_env(env);
//     return (ft_env(envp));
// }
>>>>>>>> builtin:builtin/env.c
