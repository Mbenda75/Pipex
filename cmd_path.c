/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:48:05 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/24 21:19:36 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!src || !dest)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src)) + 2);
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

int	search_path(char **env)
{
	size_t	size;
	int		index_path;

	size = 5;
	index_path = 0;
	while (env[index_path])
	{
		if (ft_strncmp("PATH=\n", env[index_path], size) == 0)
			break ;
		index_path++;
	}
	return (index_path);
}

char	*get_path(char **av, char **env, int cmd)
{
	char	*path;
	int		index_path;
	char	**array_path;
	char	**array_cmd;

	index_path = search_path(env);
	array_path = ft_split(env[index_path], ':');
	index_path = 0;
	if (cmd == 0)
		array_cmd = ft_split(av[2], ' ');
	else if (cmd == 1)
		array_cmd = ft_split(av[3], ' ');
	
	while (array_path[index_path])
	{
		path = ft_strcat(array_path[index_path], array_cmd[0]);
		if (!path)
			break;
		if (access(path, F_OK) == 0)
		{
			free_str(array_path);
			free_str(array_cmd);
			printf("path == %s\n", path);
			return(path);				
		}
		free(path);    
		index_path++;
	}
	free_str(array_path);
	free_str(array_cmd);
	return(NULL);
}
