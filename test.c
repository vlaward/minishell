#include "minishell.h"

int	main(int args, char **argv)
{
	if (execve(argv[1], &argv[1], NULL) == -1 )
		printf("wtf ??\n");

}