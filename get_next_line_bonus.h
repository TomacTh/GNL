/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:34:08 by tcharvet          #+#    #+#             */
/*   Updated: 2021/01/26 13:59:05 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif
# ifndef MAX_FD
#  define MAX_FD 256  
# endif

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

int			get_next_line(int const fd, char **line);
size_t		ft_strlen(const char *str);
char		*ft_strchr(char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
int			update_remainder(char *str, char **remainder);
int			ft_remainder(char **remainder, char **str, char *nextline);
int			protect_malloc_and_free(char *str);
int			read_loop(char **line, char **remainder, int fd, char *nextline);

#endif
