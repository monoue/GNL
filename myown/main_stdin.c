#include "get_next_line.h"

int main()
{
	char 	*line;
	int		ret;

	while ((ret = get_next_line(0, &line)))
	{
		printf("%s\n", line);
		free(line);
		if (ret == -1)
			break ;
	}
	return (1);
}
