/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:14:11 by monoue            #+#    #+#             */
/*   Updated: 2020/07/20 16:39:13 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_index_of_new_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (NOT_FOUND);
}

static int		free_and_return_error(char **stack, char *buff)
{
	free(stack);
	free(buff);
	return (ERROR);
}

static int		get_until_new_line(int fd, char **stack, int *nl_index)
{
	char	*buff;
	char	*tmp;
	int		read_ret;

	if (!(buff = malloc(sizeof(*buff) * (BUFFER_SIZE + 1))))
		return (ERROR);
	while ((read_ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_ret] = '\0';
		tmp = ft_strjoin(*stack, buff);
		free(*stack);
		if (!tmp)
			return (free_and_return_error(stack, buff));
		*stack = tmp;
		if ((*nl_index = get_index_of_new_line(*stack)) != NOT_FOUND)
			break ;
	}
	if (read_ret == FILE_END)
		*nl_index = get_index_of_new_line(*stack);
	free(buff);
	if (read_ret > 0)
		return (NOT_EOF);
	return (read_ret);
}

int				get_next_line(int const fd, char **line)
{
	static char	*fd_arr[MAX_FD + 1];
	char		*fd_src;
	int			read_status;
	int			nl_index;

	if (fd > MAX_FD || fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!fd_arr[fd] && !(fd_arr[fd] = ft_strdup("")))
		return (ERROR);
	read_status = get_until_new_line(fd, &fd_arr[fd], &nl_index);
	if (read_status == ERROR)
		return (ERROR);
	if (read_status == FILE_END && nl_index == NOT_FOUND)
	{
		*line = ft_strdup(fd_arr[fd]);
		free(fd_arr[fd]);
		fd_arr[fd] = NULL;
		return (*line ? FILE_END : ERROR);
	}
	*line = ft_substr(fd_arr[fd], 0, nl_index);
	fd_src = ft_strdup(fd_arr[fd] + nl_index + 1);
	free(fd_arr[fd]);
	fd_arr[fd] = fd_src;
	return ((fd_arr[fd] && *line) ? NOT_EOF : FILE_END);
}

#include <fcntl.h>
#include <stdio.h>

int		main(int argc, char **argv)
{
	char	*line;
	int		ret;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		printf("%s\n", line);
		free(line);
		if (ret == FILE_END)
			break ;
	}
	close(fd);
}
