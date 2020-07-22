#include "get_next_line.h"

int	main(int ac, char **av)
{
	int		fd[10];
	char	*line;
	int		ret;
	int		len;

	write(1, "\n", 1);

	// fd[0] = open("lorem.txt", O_RDONLY);
	fd[0] = open("cats.txt", O_RDONLY);
	len = 6;
	while ((ret = get_next_line(fd[0], &line) > 0) && len-- > 0)
	{
		printf("fd: %d	%s\n", fd[0], line);
		free(line);
	}
	free(line);
	// fd[1] = open("cicero.txt", O_RDONLY);
	// len = 6;
	// while ((ret = get_next_line(fd[1], &line) > 0) && len-- > 0)
	// {
	// 	printf("fd: %d	%s\n", fd[1], line);
	// 	free(line);
	// }
	// free(line);
	// fd[2] = open("kafka.txt", O_RDONLY);
	// len = 6;
	// while ((ret = get_next_line(fd[2], &line) > 0) && len-- > 0)
	// {
	// 	printf("fd: %d	%s\n", fd[2], line);
	// 	free(line);
	// }
	// free(line);
	// fd[3] = open("werther.txt", O_RDONLY);
	// len = 6;
	// while ((ret = get_next_line(fd[3], &line) > 0) && len-- > 0)
	// {
	// 	printf("fd: %d	%s\n", fd[3], line);
	// 	free(line);
	// }
	// free(line);
	close(fd[0]);
	// close(fd[1]);
	// close(fd[2]);
	// close(fd[3]);
	// while (1);
}
