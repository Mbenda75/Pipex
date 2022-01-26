/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:43 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/26 19:07:39 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	cmd_notfound(t_pipex pipex)
{
	write(1, "command not found\n", 19);
	close_fd(pipex.fds);
	free_str(pipex.cmdarg);
	exit(1);
}

void	free_str(char **s)
{
	int	line;

	line = 0;
	while (s[line])
	{
		free(s[line]);
		line++;
	}
	free(s);
}

void	dup_andclose_fd(bool fork_nb, t_pipex pipex)
{
	if (access(pipex.path, F_OK) == -1)
	{
		free(pipex.path);
		cmd_notfound(pipex);
	}
	if (fork_nb == 0)
		dup2(pipex.fds[2], STDIN_FILENO);
	else
		dup2(pipex.fds[3], STDOUT_FILENO);
	close(pipex.fds[fork_nb]);
	dup2(pipex.fds[!fork_nb], !fork_nb);
	close(pipex.fds[!fork_nb]);
}

void	exec_cmd(char **av, char **env, t_pipex pipex, int fork_nb)
{
	if (read(1, av[2], O_RDONLY) == -1 || read(1, av[3], O_RDONLY) == -1)
	{

		printf("ici\n");
		exit(1);
	}
	pipex.cmdarg = ft_split(av[fork_nb + 2], ' ');
	pipex.path = get_path(av, env, fork_nb, pipex);
	if (pipex.path == NULL)
		cmd_notfound(pipex);
	dup_andclose_fd((bool)fork_nb, pipex);
	if (access(pipex.path, F_OK) == 0)
		execve(pipex.path, pipex.cmdarg, env);
}
