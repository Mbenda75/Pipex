/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:43:15 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/22 12:24:25 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>

char		*ft_strcat(char *dest, char *src);
char		**ft_split(const char *str, char c);
char		*get_path(char **av, char **env, int cmd);
void		dup_close_fd(char *path, int file_fd, bool index_pfd, int *pfd);
void		free_str(char **s);
void		close_fd(int *pfd, int outfile, int infile);
void		exec_cmd(char **av, char **env, int *pfd, int file_fd);
int			pipex(int infile, int outfile, char **av, char **env);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *str);

#endif
