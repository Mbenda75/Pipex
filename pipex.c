/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:30:07 by benmoham          #+#    #+#             */
/*   Updated: 2021/12/28 18:07:41 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


static char	*ft_strnndup(const char *s1, int c)
{
	int		i;
	char	*str;

	i = 0;
	while (s1[i] && s1[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * ++i);
	if (!str)
		return (0);
	i = 0;
	while (s1[i] && s1[i] != c)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_counting(const char *str, char c)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			nb++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (nb);
}

char	**ft_split(const char *str, char c)
{
	int		i;
	int		k;
	char	**tab;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_counting(str, c) + 1));
	if (!tab)
		return (0);
	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			tab[k] = ft_strnndup(str + i, c);
			k++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	tab[k] = 0;
	return (tab);
}
char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;
	char *tmp;
	
	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (strlen(dest) + strlen(src))+ 1);
	while (dest[i])
	{
		tmp[i] = dest[i];
		i++;
	}
	tmp[i++] = '/';
	while (src[j])
	{
		tmp[i] = src[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*get_path(char **av, char **env)
{
	
	char	*goodpath;
	int		p;
	char	**s;
    size_t	i;
	
    i = 5;
	p = 0;
    while (env[p])
    {
        if (strncmp("PATH=\n", env[p], i) == 0)   
            break ;
        p++;
    }
    s = ft_split(env[p], ':');
	i = 8;
    p = 0;
    while (s[p])
    {
		if (strncmp("/usr/bin", s[p], i) == 0)
			break;
		p++;
    }
	goodpath = ft_strcat(s[p], av[1]);
	return(goodpath);
}
int main(int ac, char **av, char **env)
{
	char *path;
	int	pid;
	int	pid2;
	int pfd[2];
	char	**goodarg;
	
    if (pipe(pfd) == -1)
    {
       printf("pipe failed\n");
       return 1;
    }
	path = get_path(av, env);
	if ((pid = fork()) == -1)
    {
      perror("fork failed");
      return 1;
    }
   	if (pid == 0)
	{
		goodarg = ft_split(av[3], ' ');
		dup2(pfd[1], STDOUT_FILENO);  
		close(pfd[0]);
		close(pfd[1]);
		printf("goodarg2 == %s", goodarg[0]);
		execve(path, goodarg, env);
	}
 	if ((pid2 = fork()) == -1)
    {
      perror("fork failed");
      return 1;
    }
	if (pid2 == 0)
	{
		goodarg = ft_split(av[3], ' ');
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		close(pfd[1]);
		printf("goodarg2 == %s", goodarg[0]);
		execve(path, goodarg, env);
	} 
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0); 
}