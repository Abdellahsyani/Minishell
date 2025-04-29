/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/26 17:04:25 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

// int main() {
//     char *tty = ttyname(STDOUT_FILENO);  // STDIN_FILENO == 0

//     if (tty != NULL) 
//         printf("This terminal is: %s\n", tty);
//     return 0;
// }
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, how are you?";
    char *token;

    // Get the first token
    token = strtok(str, " ,?");

    // Loop through all tokens
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, " ,?");  // Continue with the next token
    }

    return 0;
}

