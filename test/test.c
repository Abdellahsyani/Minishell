/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/07 10:33:17 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    
    int pid;
    int pid2;
    int status;
    
    pid = fork();
   // pid2 = fork();
    if (pid < 0)
    {
        printf("fork faild.\n");
        return (1);
    }
    else if (pid > 0)
    {
        wait(&status);
        printf("parent process.\n");
        printf("%d",WEXITSTATUS(status));
    }
    else
    {
        printf("child process.\n");
        return (1);
    }
    return 0;
}

