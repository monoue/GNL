#define NOT_EOF		1
#define FILE_END	0
#define ERROR		-1
#define NOT_FOUND	-1
#define MAX_FD		256

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char		*ft_strdup(const char *s1)
{
	char	*d;
	size_t	i;

	i = 0;
	d = malloc(sizeof(*d) * ft_strlen(s1));
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	return (d);
}

static int	get_index_of_new_line(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (NOT_FOUND);
}

int			get_until_new_line(int fd, char **fd_str)
{
	int		read_ret;
	char	*fd_src;
	char	*buff;

	if (!(buff = malloc(sizeof(*buff) * (BUFFER_SIZE + 1))))
		return (ERROR);
	read_ret = read(fd, buff, BUFFER_SIZE);
	buff[read_ret] = '\0';

}

int			get_next_line(int fd, char **line)
{
	int			read_status;
	static char	*fd_arr[MAX_FD + 1];

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0 || !*line)
		return (ERROR);
	if (!(fd_arr[fd]) && !(fd_arr[fd] = ft_strdup("")))
		return (ERROR);
	read_status = get_until_new_line(fd, &fd_arr[fd]);
}

#include <fcntl.h>
int main(int argc, char **argv)
{
	int		fd;
	int		gnl_ret;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	while ((gnl_ret = get_next_line(fd, &line)) > 0)
		printf("%s\n", line);
	printf("%s\n", line);
	free(line);
	close(fd);
}