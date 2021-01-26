/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:02:11 by tcharvet          #+#    #+#             */
/*   Updated: 2021/01/25 20:46:15 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	char		*begin;
	char const	*s1begin;

	if (!s1 || !s2)
		return (0);
	if (!(str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	begin = str;
	s1begin = s1;
	while (*(char *)s1)
	{
		*str = *(char *)s1;
		s1++;
		str++;
	}
	while (*(char *)s2)
	{
		*str = *(char *)s2;
		s2++;
		str++;
	}
	*str = '\0';
	free((char*)s1begin);
	return (begin);
}

char	*ft_strdup(const char *s1)
{
	char		*str;
	int			i;

	i = 0;
	while (s1[i])
		i++;
	if (!(str = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

int		protect_malloc_and_free(char *str)
{
	free(str);
	return (-1);
}
