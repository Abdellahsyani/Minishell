/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:35:20 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/12 10:46:04 by abhimi           ###   ########.fr       */
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
    while (j < i)
    {
        key[j] = str[j];
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
    int l= strlen(str);
    while (str[i] && str[i] != '=')
        i++;
    i++;
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

t_env *new_node(char *key, char *value)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    if(!new)
        return (NULL);
    new->key = key;
    // free(key);
    new->value = value;
    // if(value)
    //     free(value);
    new->next = NULL;
    return (new);
}
t_env   **get_env(char **list)
{
    int i = 0;
    t_env **tmp;
    t_env *cur;
    
    cur = new_node(ft_key(*list), get_value(*list));
    list++;
    *tmp = cur;
    while (*list)
    {
        cur->next = new_node(ft_key(*list), get_value(*list));
        cur = cur->next;
        list++;
    }
    return (tmp);
}

// int main(int ac, char **arg, char **env)
// {
//     (void)ac;
//     (void)arg;
//     t_env **cur;

//     cur = get_env(env);
//     while (*cur)
//     {
//         printf("%s=%s\n",(*cur)->key,(*cur)->value);
//         (*cur) = (*cur)->next;
//     }
//     return 0;
// }