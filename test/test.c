/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/08 17:06:54 by abhimi           ###   ########.fr       */
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
    int pipefd[2];
    char str[10];
    char s[10] = "hello man\n";
    
    pid = fork();

   if (pipe(pipefd) == -1)
   {
        perror("pipe");
        return (1);
   }
    if (pid < 0)
    {
        printf("fork faild.\n");
        return (1);
    }
    else if (pid > 0)
    {
        close(pipefd[0]);
        printf("I am writing now in pipe from child process.\n");
        write(pipefd[1],s, 11);
        close(pipefd[1]);
        wait(NULL);

    }
    else
    {
        
        close(pipefd[1]);
        read(pipefd[0],str, 10);
        printf("I read from pipe:%s\n",str);
        close(pipefd[0]);
    }
    return 0;
}

