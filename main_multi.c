#include "get_next_line.h"

int	main(int ac, char **av)
{
	char	*line1;
	char	*line2;
	int		fd1;
	int		fd2;

	if (ac > 0)
	{
		fd1 = open(av[1], O_RDONLY);
		fd2 = open(av[2], O_RDONLY);
		get_next_line(fd1, &line1);
		printf("%%s\n", line1);
		get_next_line(fd1, &line1);
		printf("%%s\n", line1);
		get_next_line(fd2, &line2);
		printf("%%s\n", line2);
		get_next_line(fd1, &line1);
		printf("%%s\n", line1);
		get_next_line(fd2, &line2);
		printf("%%s\n", line2);
	}
	return (0);
}
