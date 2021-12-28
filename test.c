/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:47:07 by benmoham          #+#    #+#             */
/*   Updated: 2021/12/27 15:09:20 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int
main(int argc, char *argv[], char *env[])
{
  pid_t          pid;
  int            status;
  int            pipe_fd[2];

  if (argc < 2)
    return 1;

  if (pipe(pipe_fd) == -1)
    {
      perror("pipe");
      return 1;
    }

  if ((pid = fork()) == -1)
    {
      perror("fork");
      return 1;
    }
  else if (pid == 0)
    {
      close(pipe_fd[0]);
      write(pipe_fd[1], argv[1], strlen(argv[1]));
      close(pipe_fd[1]);
      return 1;
    }
  else
    {
      char          buffer[1024];
      int           ret;

      close(pipe_fd[1]);
      while ((ret = read(pipe_fd[0], buffer, 1023)))
        {
          buffer[ret] = 0;
          printf("%s\n", buffer);
        }
      close(pipe_fd[0]);
    }

  return 0;
}
int main(int ac, char **av)
{
    int pid;
    pid = fork();
    if (pid != 0)
        fork();
    
    printf("je suis ici\n");
}