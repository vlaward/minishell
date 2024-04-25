#include "minishell.h"



int	main()
{
	char	**cat;
	char	**cat2;
	int		pipette[2];
	int		status;

	status = 0;
	pipe(pipette);
	cat = NULL;
	cat = ft_split("/bin/cat test", ' ');
	cat2 = ft_split("/bin/cat txt", ' ');
	if (!fork())
	{
		dup2(pipette[1], STDOUT_FILENO);
		execve(cat[0], cat, NULL);
	}
	else
	{
		dup2(pipette[0], STDIN_FILENO);
		execve(cat2[0], cat2, NULL);
		// write(1, "Petite putain\n\0", 15);//on devrtais pouvoir directement ecrire dans pipe
	
	}
	return(0);
}