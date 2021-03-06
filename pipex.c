/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:30:07 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/22 17:54:40 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int *pfd, int outfile, int infile)
{
	close(pfd[0]);
	close(pfd[1]);
	close(infile);
	close(outfile);
}

int	pipex(int infile, int outfile, char **av, char **env)
{
	int	child;
	int child2;
	int	pfd[2];

	if (pipe(pfd) == -1)
	{
		printf("pipe failed\n");
		return (-1);
	}
	child = fork();
	if (child == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (child == 0){
		printf("first1\n");
		exec_cmd(av, env, pfd, infile);
		}
	child2 = fork();
	if (child2 == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (child2 == 0){
		printf("first2\n");
		exec_cmd(av, env, pfd, outfile);
	}
	close_fd(pfd, outfile, infile);
	waitpid(child, NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	infile;
	int	outfile;
	if (ac != 5)
		exit(1);
	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		return (-1);
	pipex(infile, outfile, av, env);
}
