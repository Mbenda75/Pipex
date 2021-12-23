/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:30:07 by benmoham          #+#    #+#             */
/*   Updated: 2021/12/23 17:56:09 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void	parse_pipe(char **av)
{
	
}
int main(int ac, char **av, char **env)
{
    int	p;
	char	**s;
	char	**s2;
    size_t i;
	
    i = 5;
	p = 0;
    while (env[p])
    {
        if (strncmp("PATH=", env[p], i) == 0)
        {	   
			printf("trouve Path = %s\n", env[p]);
            break ;
        }
        p++;
    }
    s = ft_split(env[p], ':');
	i = 8;
    p = 0;
    while (s[p])
    {
		if (strncmp("/usr/bin", s[p], i) == 0)
		{
        	printf("Good PAth = %s\n", s[p]);
			break;
		}
		p++;
    }
    s2 = ft_split(av[1], ' ');
    execve("/usr/bin/", s2, NULL); 
}