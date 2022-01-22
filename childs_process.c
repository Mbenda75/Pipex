/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:43 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/22 17:37:21 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	dup_andclose_fd(bool fork_nb, t_pipex pipex)
{
	printf("path = %s\n", pipex.path);
	if (access(pipex.path, F_OK) == -1)
	{
		perror("command not found\n");
		free_str(pipex.cmdarg);
		free(pipex.path);
		exit(1);
	}

	dup2(pipex.fds[fork_nb], fork_nb); // 0 & 1
	close(pipex.fds[fork_nb]);
	dup2(pipex.fds[fork_nb + 2], !fork_nb);
	close(pipex.fds[fork_nb]);
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

void	exec_cmd(char **av, char **env, t_pipex pipex, int fork_nb)
{	
	pipex.cmdarg = ft_split(av[fork_nb + 2], ' ');
	pipex.path = get_path(av, env, fork_nb);

	dup_andclose_fd((bool)fork_nb, pipex);
	
	if (access(pipex.path, F_OK) == 0)
		execve(pipex.path, pipex.cmdarg, env);
}