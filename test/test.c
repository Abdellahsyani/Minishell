/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/30 11:26:28 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>

int main() {

    char *input;
    input = readline("enter smithing : ");
    if(input)
    {
        rl_replace_line("This is new line", 0);
        write(1,"\n",1);
        rl_redisplay();
        free(input);
    }
    return (0);
}

