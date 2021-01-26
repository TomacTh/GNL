/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:30:17 by tcharvet          #+#    #+#             */
/*   Updated: 2021/01/26 14:43:43 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	update_remainder(char *str, char **remainder)
{
	char		*tmp;

	tmp = 0;
	if (remainder && *remainder)
		tmp = *remainder;
	if (!(*remainder = ft_strdup(str)))
	{
		if (tmp)
			free(tmp);
		return (0);
	}
	if (tmp)
		free(tmp);
	tmp = 0;
	return (1);
}

int	ft_remainder(char **remainder, char **str, char *nextline)
{
	if (remainder && *remainder)
	{
		if ((nextline = ft_strchr(*remainder)))
		{
			*nextline = '\0';
			if (!(*str = ft_strjoin(*str, *remainder)))
			{
				free(*str);
				return (protect_malloc_and_free(*remainder));
			}
			if (!(update_remainder(++(nextline), remainder)))
				return (protect_malloc_and_free(*str));
			return (1);
		}
		if (!(*str = ft_strjoin(*str, *remainder)))
		{
			free(*remainder);
			*remainder = 0;
			return (protect_malloc_and_free(*str));
		}
		free(*remainder);
		*remainder = 0;
	}
	return (0);
}

int	read_loop(char **line, char **remainder, int fd, char *nextline)
{
	char		buff[BUFFER_SIZE + 1];
	int			size;

	while ((size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[size] = '\0';
		if ((nextline = ft_strchr(buff)))
		{
			*nextline = '\0';
			if (!(*line = ft_strjoin(*line, buff)))
			{
				free(*line);
				return (-1);
			}
			if (nextline < &buff[size - 1])
				update_remainder(++(nextline), remainder);
			return (1);
		}
		if (!(*line = ft_strjoin(*line, buff)))
			return (protect_malloc_and_free(*line));
	}
	return ((*remainder && !size) ? 1 : size);
}

int	get_next_line(const int fd, char **line)
{
	static char	*remainder;
	char		*nextline;
	int			result;
	
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FD + 1 || !line)
		return (-1);
	if(!(*line = malloc(sizeof(char) * 1)))
		return (-1);
	**line = '\0';
	nextline = 0;
	if ((result = ft_remainder(&remainder, line, nextline)) == 1)
		return (1);
	else if (result == -1)
		return (-1);
	return (read_loop(line, &remainder, fd, nextline));
}
