/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:24:36 by amakela           #+#    #+#             */
/*   Updated: 2024/09/24 14:56:04 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	find_nl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i++] == '\n')
			return (1);
	}
	return (0);
}

void	freeptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*next_line(char **text_read, ssize_t bytes_read, char *line, int *flag)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*text_read)[i] != '\0' && (*text_read)[i] != '\n')
		i++;
	if ((*text_read)[i] == '\n')
		i++;
	line = ft_substr(*text_read, 0, i);
	if (!line)
		return (set_err(flag));
	if (bytes_read == 0)
		return (line);
	temp = *text_read;
	*text_read = ft_substr(*text_read, i, ft_strlen(*text_read) - i);
	freeptr(&temp);
	if (!*text_read)
	{
		freeptr(&line);
		return (set_err(flag));
	}
	return (line);
}

ssize_t	read_file(int fd, char **text_read, ssize_t bytes_read, int *flag)
{
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];

	while (!find_nl(*text_read))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
			break ;
		buffer[bytes_read] = '\0';
		temp = *text_read;
		*text_read = ft_strjoin(*text_read, buffer);
		freeptr(&temp);
		if (!*text_read)
		{
			set_err(flag);
			return (-1);
		}
	}
	if ((bytes_read == -1) || (bytes_read == 0 && **text_read == '\0'))
	{
		freeptr(text_read);
		return (-1);
	}
	return (bytes_read);
}

char	*get_next_line(int fd, int *flag)
{
	char		*line;
	ssize_t		bytes_read;
	static char	*text_read[MAX_FD];

	line = 0;
	bytes_read = 1;
	if (fd < 0)
		return (set_err(flag));
	if (!text_read[fd])
		text_read[fd] = (char *)ft_calloc(1, 1);
	if (!text_read[fd])
		return (set_err(flag));
	if (read(fd, 0, 0) < 0)
	{
		freeptr(&text_read[fd]);
		return (set_err(flag));
	}
	bytes_read = read_file(fd, &text_read[fd], bytes_read, flag);
	if (bytes_read == -1)
		return (NULL);
	line = next_line(&text_read[fd], bytes_read, line, flag);
	if (!line || bytes_read == 0)
		freeptr(&text_read[fd]);
	return (line);
}
