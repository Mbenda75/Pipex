/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:50:08 by benmoham          #+#    #+#             */
/*   Updated: 2021/12/23 14:14:31 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
 
 
int main( int argc, char ** argv )
{
    /* create the pipe */
   int pfd[2];
   if (pipe(pfd) == -1)
    {
       printf("pipe failed\n");
       return 1;
    }
 
   /* create the child */
   int pid;
   if ((pid = fork()) < 0)
    {
        printf("fork failed\n");
        return 2;
    }
 
   if (pid == 0)
    {
        /* child */
        dup2(pfd[0], 0); /* connect the read side with stdin */
        close(pfd[0]); /* close the unused write side */
        close(pfd[1]); /* close the read side */
        /* execute the process (wc command) */
        execlp("ls", "ls", NULL);
        printf("wc failed"); /* if execlp returns, it's an error */
        return 3;
    }
   else
    {
       /* parent */
        dup2(pfd[1], 1); /* connect the write side with stdout */
        close(pfd[0]); /* close the unused read side */
        close(pfd[1]); /* close the write side */
        /* execute the process (ls command) */
        execlp("ls", "ls", NULL);
        printf("ls failed"); /* if execlp returns, it's an error */
        return 4;
    }
    return 0;
}
