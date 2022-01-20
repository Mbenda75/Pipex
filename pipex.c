/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:30:07 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/20 15:13:50 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void close_fd(int *pfd, int outfile, int infile)
{
	close(pfd[0]);
	close(pfd[1]);
	close(infile);
	close(outfile);	
}

int	pipex(int infile, int outfile ,char **av, char **env)
{
	int	child;
	int child2;
	int pfd[2];
	
	if (pipe(pfd) == -1)
	{
		printf("pipe failed\n");
		return (-1);
	} 
	if(child = fork() == -1)
	{
		perror("fork failed");
		return (-1);
	}
  	if (child == 0)
		child_process(av, env, infile, pfd);
	if(child2 = fork() == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (child2 == 0)
		child2_process(pfd, env, av, outfile);
	close_fd(pfd, outfile, infile);
	waitpid(child, NULL, 0);
	waitpid(child2, NULL, 0); 
}

int main(int ac, char **av, char **env)
{
	char *path;
	char	**cmdarg;
	

		 cmdarg = ft_split(av[2], ' ');
		 printf("Garg= %s\n", cmdarg[1]); 
		 path = get_path(av, env, 1);
		 printf("path= %s\n", path);
		 cmdarg = ft_split(av[3], ' ');
		 printf("Garg= %s\n", cmdarg[1]); 
		 path = get_path(av, env, 2);
		 printf("path= %s\n", path); 
/* 	int infile = open(av[1], O_RDONLY);
	int outfile = open(av[4], O_RDONLY, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		return (-1);
	pipex(infile, outfile, av, env); */
}  
