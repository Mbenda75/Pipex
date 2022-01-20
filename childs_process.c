/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:43 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/20 15:14:09 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child2_process(int *pfd, char **env, char **av, int outfile)
{
	char **cmdarg;
	char *path;
	
	cmdarg = ft_split(av[3], ' ');
	path = get_path(av, env, 2);	
	close(pfd[1]);
	dup2(outfile, STDOUT_FILENO);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	execve(path, cmdarg, env);
}

void	child_process(char **av, char **env, int infile, int *pfd)
{
	char **cmdarg;
	char *path;
	
  	path = get_path(av, env, 1);
	cmdarg = ft_split(av[2], ' ');
	dup2(infile, STDIN_FILENO);
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	execve(path, cmdarg, env);
}