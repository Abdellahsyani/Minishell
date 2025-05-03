/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:35:20 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/03 18:59:49 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_key(char *str)
{
    int i;
    int j = 0;
    i = 0;
    char *key;
    
    while (str[i] && str[i] != '=')
        i++;
    key = malloc(sizeof(char) * (i + 1));
    if (!key)
        return (NULL);
    while (j <= i)
    {
        str[j] = key[j];
        j++;
    }
    key[j] = '\0';
    return (key);
}

char    *get_value(char *str)
{
    int i;
    char *value;
    int j = 0;
    i = 0;
    printf("%s\n", str);
    int l= strlen(str);
    while (str[i] && str[i] != '=')
        i++;
    i += 1;
    value = malloc(sizeof(char) * (l - i + 1));
    if (!value)
        return NULL;
    while (i < l)
    {
        value[j] = str[i];
        j++;
        i++;
    }
    value[j] = '\0';
    return (value);
}
t_env   *get_env(char **list)
{
    t_env *env;

    while (*list != NULL)
    {
        env = malloc(sizeof(t_env));
        env->key = ft_key(*list);
        env->value = get_value(*list);
        env = env->next;
        list++;
    }
    return (env);
}

int main(int ac, char **arg, char **env)
{
    (void)ac;
    (void)arg;
    t_env *cur;

    cur = get_env(env);
    while (cur)
    {
        printf("%s = %s\n",cur->key,cur->value);
        cur = cur->next;
    }
    return 0;
}