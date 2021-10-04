#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd[10];
	char	*line;
	int		ret;
	int		len;

	(void)argc;
	(void)argv;
	write(1, "\n", 1);

	fd[0] = open("lorem.txt", O_RDONLY);
	len = 6;
	while ((ret = get_next_line(fd[0], &line) > 0) && len-- > 0)
	{
		printf("fd: %d	%s\n", fd[0], line);
		free(line);
	}
	free(line);
	close(fd[0]);
}
