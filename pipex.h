/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:43:15 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/21 18:12:10 by benmoham         ###   ########.fr       */
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
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

char	    *ft_strcat(char *dest, const char *src);
char	    *get_path(char **av, char **env, int cmd);
char	    **ft_split(const char *str, char c);
static char	*ft_strnndup(const char *s1, int c);
static int	ft_counting(const char *str, char c);
void        close_fd(int *pfd, int outfile, int infile);
int         pipex(int infile, int outfile ,char **av, char **env);
void        exec_cmd(char **av, char **env, int *pfd, int file_fd);
int	        ft_strncmp(const char *s1, const char *s2, size_t n);
void	    dup_close_fd(char	*path, int file_fd, bool index_pfd, int *pfd);
void        free_str(char **s);
#endif