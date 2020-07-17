#include "get_next_line.h"

int	main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		ret;
	int		i;

	i = 1;
	if (ac > 0)
	{
		printf("====================result====================\n");
		fd = open(av[1], O_RDONLY);
		while ((ret = get_next_line(fd, &line)))
		{
			printf("%d:%s\n", i++, line);
			free(line);
			if (ret == -1)
				break ;
		}
		free(line);
		printf("%d:%s\n", i, line);
		printf("====================result====================\n");
	}
	// while(1)
	//  	;
	return (0);
}
