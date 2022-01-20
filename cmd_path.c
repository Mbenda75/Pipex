/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:48:05 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/20 12:48:30 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*get_path(char **av, char **env, int cmd)
{

	char	*goodpath;
	int		p;
	char	**s;
	char	**str;
	size_t	y;

	y = 5;
	p = 0;
	while (env[p])
	{
		if (strncmp("PATH=\n", env[p], y) == 0)   
			break ;
		p++;
	}
	s = ft_split(env[p], ':');
	y = 8;
	p = 0;
	while (s[p])
	{
		if (strncmp("/usr/bin", s[p], y) == 0)
			break;
		p++;
	}
	if (cmd == 1)
		str = ft_split(av[2], ' ');
	else if (cmd == 2)
		str = ft_split(av[3], ' ');
	goodpath = ft_strcat(s[p], str[0]);
	return(goodpath);
}