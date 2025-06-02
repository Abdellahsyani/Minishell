/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/30 15:44:17 by abhimi           ###   ########.fr       */
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
    printf("%s\n", input);
    return (0);
}

