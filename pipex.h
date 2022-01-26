/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:43:15 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/26 17:47:03 by benmoham         ###   ########.fr       */
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

typedef struct s_pipex
{
	int		child;
	int		fds[4];
	int		infile;
	int		outfile;
	char	*path;
	char	**array_path;
	char	**array_cmd;
	char	**cmdarg;
}		t_pipex;

void		dup_andclose_fd(bool fork_nb, t_pipex pipex);
void		free_str(char **s);
void		close_fd(int *fds);
void		fork_routine(char **av, char **env, t_pipex pipex);
void		cmd_notfound(t_pipex pipex);
void		exec_cmd(char **av, char **env, t_pipex pipex, int fork_nb);
int			pipex(int infile, int outfile, char **av, char **env);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *str);
char		*check_path(char **av, int cmd, char **array_path, t_pipex pipex);
char		*boucle_path(char **array_path, int index_path, char **array_cmd);
char		**get_arraycmd(int cmd, char **av);
char		*ft_strdup(char *s);
char		*ft_strcat(char *dest, char *src);
char		**ft_split(const char *str, char c);
char		*get_path(char **av, char **env, int cmd, t_pipex pipex);

#endif
