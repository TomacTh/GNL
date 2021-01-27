/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:02:38 by tcharvet          #+#    #+#             */
/*   Updated: 2021/01/27 21:09:59 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	update_remainder(char *str, char **remainder, char *buff)
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
	if(buff)
		free(buff);
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
			if (!(update_remainder(++(nextline), remainder, 0)))
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
	char		*buff;
	int			size;

	if(!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
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
				update_remainder(++(nextline), remainder, buff);
			return (1);
		}
		if (!(*line = ft_strjoin(*line, buff)))
			return (protect_malloc_and_free(*line));
	}
	return ((*remainder && !size) ? 1 : size);
}

int	get_next_line(const int fd, char **line)
{
	static char	*remainder[MAX_FD + 1];
	char		*nextline;
	int			result;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if(!(*line = malloc(sizeof(char) * 1)))
		return (-1);
	**line = '\0';
	nextline = 0;
	if ((result = ft_remainder(&remainder[fd], line, nextline)) == 1)
		return (1);
	else if (result == -1)
		return (-1);
	return (read_loop(line, &remainder[fd], fd, nextline));
}
