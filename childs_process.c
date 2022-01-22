/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:43 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/22 11:42:41 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_andclose_fd(char *path, int file_fd, bool index_pfd, int *pfd)
{
	if (access(path, F_OK) == -1)
	{
		perror("cmd not found\n");
		exit (1);
	}
	dup2(file_fd, !index_pfd);
	close(pfd[!index_pfd]);
	dup2(pfd[index_pfd], index_pfd);
	close(pfd[index_pfd]);
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

void	exec_cmd(char **av, char **env, int *pfd, int file_fd)
{
	char	**cmdarg;
	char	*path;
	bool	index_pfd;
	int		index_av;
	int		cmd;

	if (file_fd == 3)
	{
		cmd = 1;
		index_pfd = true;
		index_av = 2;
	}
	else if (file_fd == 4)
	{
		cmd = 2;
		index_pfd = false;
		index_av = 3;
	}
	cmdarg = ft_split(av[index_av], ' ');
	path = get_path(av, env, cmd);
	dup_andclose_fd(path, file_fd, index_pfd, pfd);
	if (access(path, F_OK) == 0)
		execve(path, cmdarg, env);
	free_str(cmdarg);
	free(path);
}
