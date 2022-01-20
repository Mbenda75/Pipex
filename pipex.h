/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:43:15 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/20 14:02:02 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

char	    *ft_strcat(char *dest, const char *src);
char	    *get_path(char **av, char **env, int cmd);
char	    **ft_split(const char *str, char c);
static char	*ft_strnndup(const char *s1, int c);
static int	ft_counting(const char *str, char c);
void	    child2_process(int *pfd, char **env, char **av, int outfile);
void	    child_process(char **av, char **env, int infile, int *pfd);
void        close_fd(int *pfd, int outfile, int infile);
int         pipex(int infile, int outfile ,char **av, char **env);

#endif