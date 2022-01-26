/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:30:07 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/26 18:39:40 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	close(fds[3]);
}

void	fork_routine(char **av, char **env, t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		pipex.child = fork();
		if (pipex.child == -1)
		{
			write(2, "fork failed\n", 13);
			close_fd(pipex.fds);
			exit (1);
		}
		if (pipex.child == 0)
			exec_cmd(av, env, pipex, i);
		i++;
	}
	close_fd(pipex.fds);
	waitpid(pipex.child, NULL, 0);
}

void	create_fds(char *infile_path, char *outfile_path, t_pipex *pipex)
{
	int	files[2];
	int	pfd[2];

	files[0] = open(infile_path, O_RDONLY);
	files[1] = open(outfile_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (files[0] < 0 || files[1] < 0)
		exit(1);
	if (pipe(pfd) == -1)
	{
		write(2, "pipe failed\n", 13);
		exit (1);
	}
	pipex->fds[0] = pfd[0];
	pipex->fds[1] = pfd[1];
	pipex->fds[2] = files[0];
	pipex->fds[3] = files[1];
}

int	ft_pipex(char **av, char **env)
{
	t_pipex	pipex;

	create_fds(av[1], av[4], &pipex);
	fork_routine(av, env, pipex);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
		exit(1);
	ft_pipex(av, env);
	return (0);
}
