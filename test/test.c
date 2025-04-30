/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:53 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/30 11:24:52 by abhimi           ###   ########.fr       */
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
#include <unistd.h>
#include <stdlib.h>
char *path(char *str)
{
    char *cwd;
    size_t size = 1024;
    (void)str;
    char t[1024];
    cwd = getcwd(t,size);
    if (!cwd)
    {
        return (NULL);
    }
    return (cwd);
}
int main() {
    

    char *cwd;
    cwd = getcwd(NULL,0);
    printf("%s\n",cwd);
    chdir("..");
    printf("%s\n", getcwd(NULL,0));
    //free(buf);
    //free(cwd); 
    return 0;
}

