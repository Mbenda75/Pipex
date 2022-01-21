/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:43 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/21 19:07:59 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_close_fd(char *path, int file_fd, bool index_pfd, int *pfd)
{
	if (access(path, F_OK) == -1)
		printf("cmd not found\n");
	dup2(file_fd, !index_pfd);
	close(pfd[!index_pfd]); //Invert so we close stdin for the first cmd and stdout for the 2nd cmXD
	dup2(pfd[index_pfd], index_pfd);
	close(pfd[index_pfd]); //Close stdout for the first cmd and stdin for the 2nd cmd
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
		cmd = 1; //	the first cmd
		index_pfd = true; // So we get index 1
		index_av = 2;// Argv[3]
	}
	else if (file_fd == 4)
	{
		cmd = 2; // the 2nd cmd
		index_pfd = false; // So get get index 0
		index_av = 3;// Argv[4]
	}
	cmdarg = ft_split(av[index_av], ' ');
	path = get_path(av, env, cmd);
	dup_close_fd(path, file_fd, index_pfd, pfd);
	if (access(path, F_OK) == 0)
		execve(path, cmdarg, env);
	free_str(cmdarg);
	free(path);
}
