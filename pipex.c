/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:30:07 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/21 13:02:49 by benmoham         ###   ########.fr       */
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

int	create_child(char **av, char **env, int *pfd, int infile, int outfile)
{
	int	child;
	int child2;
	
	child = fork();
	if(child== -1)
	{
		perror("fork failed");
		return (-1);
	}
  	if (child == 0)
	  	exec_cmd(av, env, pfd, 1, infile);
	child2 = fork();
	if (child2 == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (child2 == 0)
		exec_cmd(av, env, pfd, 2, outfile);
	close_fd(pfd, outfile, infile);
	waitpid(child, NULL, 0);
	waitpid(child2, NULL, 0);
}

int	pipex(int infile, int outfile ,char **av, char **env)
{
	int pfd[2];
	
	if (pipe(pfd) == -1)
	{
		printf("pipe failed\n");
		return (-1);
	}
	create_child(av, env, pfd, infile, outfile);
}

int main(int ac, char **av, char **env)
{
	char *path;
	char	**cmdarg;
	int	infile;
	int	outfile;
	
	if (ac != 5 )
		exit(1);
  	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
 	if (infile < 0 || outfile < 0)
		return (-1);
	pipex(infile, outfile, av, env); 
} 
