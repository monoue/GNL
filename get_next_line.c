#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*p));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
		p[i++] = *s1++;
	while (*s2 != '\0')
		p[i++] = *s2++;
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	s2 = malloc(sizeof(*s2) * (ft_strlen(s1) + 1));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int		ft_max(int n1, int n2)
{
	if (n1 >= n2)
		return (n1);
	return (n2);
}

int		ft_min(int n1, int n2)
{
	if (n1 <= n2)
		return (n1);
	return (n2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	srclen;
	size_t	minlen;
	size_t	i;

	if (s == NULL)
		return (NULL);
	srclen = ft_strlen(s);
	if (start > srclen)
		return (ft_strdup(""));
	minlen = ft_max(ft_min(srclen - start, len), 0);
	p = malloc((minlen + 1) * sizeof(*p));
	if (p == NULL)
		return (NULL);
	s += start;
	i = 0;
	while (minlen-- > 0)
		p[i++] = *s++;
	p[i] = '\0';
	return (p);
}

int	get_next_line(int const fd, char **line)
{
	int			ret;
	int			index;
	static char	*stack[MAX_FD + 1];
	char		*buff;
	char		*tmp;

	if (!stack[fd])
		stack[fd] = ft_strdup("");
	buff = malloc(sizeof(*buff) * (BUFFER_SIZE + 1)); // 終端文字分含む
	ret = read(fd, buff, BUFFER_SIZE);
	buff[ret] = '\0';
	tmp = ft_strjoin(stack[fd], buff);
	stack[fd] = tmp;
	index = 0;
	while (stack[fd][index])
	{
		if (stack[fd][index] == '\n')
			break ;
		index++;
	}
	// *line = ft_strdup(stack[fd]);
	*line = ft_substr(stack[fd], 0, index); // stack 中のはじめから index まで
	tmp = ft_strdup(stack[fd] + index + 1); // index は nl が入っているから、その次から
	return (1);
}



#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		fd;
	int		tmp;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	tmp = get_next_line(fd, &line);
	printf("%s\n", line);
	close(fd);

	// char	*line;
	// int		fd;
	// int		tmp;

	// fd = open(argv[1], O_RDONLY);
	// tmp = get_next_line(fd, &line);
	// printf("%s\n", line);
	// free(line);
	// close(fd);
	// end


	// if (argc == 2)
	// {
	// 	while ((tmp = get_next_line(fd, &line)) >= 0)
	// 	{
	// 		printf("%s\n", line);
	// 		free(line);
	// 		if (tmp == 0)
	// 			break ;
	// 	}
	// }
}