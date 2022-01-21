/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:43 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/21 13:18:33 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void  exec_cmd(char **av, char **env, int *pfd, int child_nb, int file_fd)
{
	char **cmdarg;
	char *path;
	bool index_pfd;
	int index_av;

    if (child_nb == 1)
	{
        index_pfd = true; // So we get index 1
        index_av = 2;// Argv[3]
    }
	else if (child_nb == 2)
	{
        index_pfd = false; // So get get index 0
        index_av = 3 ;// Argv[2]
    }
    cmdarg = ft_split(av[index_av], ' ');
    path = get_path(av, env, child_nb);
	if (access(path, F_OK) == -1)
		printf("cmd not found\n");
	dup2(file_fd, !index_pfd);
	close(pfd[!index_pfd]); // Invert so we close stdin
	dup2(pfd[index_pfd], index_pfd);
	close(pfd[index_pfd]); // Close stdout
	if (access(path, F_OK) == 0)
		execve(path, cmdarg, env);
}