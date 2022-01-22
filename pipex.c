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

void	close_fd(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	close(fds[3]);
}

void create_fds(char *infile_path, char *outfile_path, t_pipex *pipex) {
	int files[2];
	int pfd[2];

	files[0] = open(infile_path, O_RDONLY);
	files[1] = open(outfile_path, O_CREAT | O_RDWR | O_TRUNC, 0644);

	if (files[0] < 0 || files[1] < 0)
		printf("open failed\n");

	if (pipe(pfd) == -1)
	{
		printf("pipe failed\n");
	}

	pipex->fds[0] = files[0];
	pipex->fds[1] = files[1];
	pipex->fds[2] = pfd[0];
	pipex->fds[3] = pfd[1];
}

int	ft_pipex(char **av, char **env)
{
	t_pipex pipex;

	// fds[0] = infile
	// fds[1] = outfile
	// fds[2] = stdin_pipe
	// fds[3] = stdout_pipe

	create_fds(av[1], av[2], &pipex);

	fork_routine(av, env, pipex);
	close_fd(pipex.fds);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
		exit(1);

	ft_pipex(av, env);
}


int fork_routine(char **av, char **env, t_pipex pipex) {
	int i;

	i = 0;

	// if (file[0] < file[1])
	// {
	// 	cmd = 1;
	// 	index_pfd = true;
	// }
	// else {
	// 	cmd = 2;
	// 	index_pfd = false;
	// }

	while(i < 2) {
		pipex.child = fork();
		if (pipex.child == -1)
		{
			perror("fork failed");
			return (-1);
		}
		if (pipex.child == 0)
			exec_cmd(av, env, pipex, i);
		i++;
		waitpid(pipex.child, NULL, 0);
	}
	return (1);
}