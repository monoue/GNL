/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:14:11 by monoue            #+#    #+#             */
/*   Updated: 2020/07/17 17:28:43 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_new_line_index(char *str)
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

static int		get_to_new_line(int fd, char **stack, int *nl_index)
{
	char	*buff;
	char	*tmp;
	int		ret;

	if (!(buff = malloc(sizeof(*buff) * BUFFER_SIZE + 1)))
		return (ERROR);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = ft_strjoin(*stack, buff);
		free(*stack);
		if (!tmp)
			return (free_and_return_error(stack, buff));
		*stack = tmp;
		if ((*nl_index = get_new_line_index(*stack)) != NOT_FOUND)
			break ;
	}
	if (ret == FILE_END)
		*nl_index = get_new_line_index(*stack);
	free(buff);
	if (ret > 0)
		return (NOT_EOF);
	return (ret);
}

int				get_next_line(int const fd, char **line)
{
	static char	*stack_arr[MAX_FD + 1];
	char		*tmp;
	int			ret;
	int			nl_index;

	if (fd > MAX_FD || fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!stack_arr[fd] && !(stack_arr[fd] = ft_strdup("")))
		return (ERROR);
	ret = get_to_new_line(fd, &stack_arr[fd], &nl_index);
	if (ret == ERROR)
		return (ERROR);
	if (ret == FILE_END && nl_index == NOT_FOUND)
	{
		*line = ft_strdup(stack_arr[fd]);
		free(stack_arr[fd]);
		stack_arr[fd] = NULL;
		return (*line ? FILE_END : ERROR);
	}
	*line = ft_substr(stack_arr[fd], 0, nl_index);
	tmp = ft_strdup(stack_arr[fd] + nl_index + 1);
	free(stack_arr[fd]);
	stack_arr[fd] = tmp;
	return ((stack_arr[fd] && *line) ? NOT_EOF : FILE_END);
}

// #include <fcntl.h>
// #include <stdio.h>

// int		main(int argc, char **argv)
// {
// 	char	*line;
// 	int		ret;
// 	int		fd;

// 	fd = open(argv[1], O_RDONLY);
// 	while ((ret = get_next_line(fd, &line)) >= 0)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 		if (ret == FILE_END)
// 			break ;
// 	}
// 	close(fd);
// }

// static int	read_to_nl(int fd, char **stack_fd, int *index)
// {
// 	char	*buff;
// 	char	*tmp;
// 	int		ret;

// 	if (!(buff = malloc(sizeof(*buff) * (BUFFER_SIZE + 1))))
// 		return (ERROR);
// 	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
// 	{
// 		buff[ret] = '\0';
// 		tmp = ft_strjoin(*stack_fd, buff);
// 		free(*stack_fd);
// 		if (!tmp)
// 		{
// 			free(stack_fd);
// 			free(buff);
// 			return (ERROR);
// 		}
// 		*stack_fd = tmp;
// 		if ((index = get_new_line_index(*stack_fd)) != NOT_FOUND)
// 			break ;
// 	}
// 	free(buff);
// 	if (ret == FILE_END)
// 		*index = get_new_line_index(*stack_fd);
// 	if (ret > 0)
// 		return (NOT_EOF);
// 	return (ret);
// }