#include "minishell.h"

char	*file_name_trim(char **str)
{
	char	*ret;

	while (**str == ' ')
		(*str)++;
	ret = *str;
	while (**str && !ft_isin_table(**str, ">< "))
		(*str)++;
	if (*str == ret)
		return (NULL);
	return (ft_strndup(ret, *str - ret));
}

int	redirect_fork(pid_t in, char *end)
{
	char	*tmp;
	int		pipette[2];
	char	*towrite;
	struct stat	stats;

	if (in == -1)
		return (0);
	towrite = NULL;
	pipe(pipette);
	if (!fork())
	{
		close(pipette[0]);
		dup2(in, STDIN_FILENO);
		fstat(in, &stats);
		fprintf(stderr, "ceci est le char : %d\n", S_ISCHR(stats.st_mode));
		tmp = readline("> ");
		while (tmp != NULL)
		{

			// fprintf(stderr, "ca vas ici : %s\n", towrite);
			if ( end == NULL || !ft_strcmp(end, tmp))//verifier si overlap pas ex : str="dacord" end="dac"
				(write(pipette[1], towrite, ft_strlen(towrite)), free(tmp), free(towrite), exit(0));
			towrite = ft_strjoin_n_free(towrite, ft_strdup(tmp));
			towrite = ft_strjoin_n_free(towrite, ft_strdup("\n"));
			free(tmp);
			tmp = readline("> ");
		}
		(close(in),close(pipette[1]));
		exit(0);
	}
	if (dup2(pipette[0], STDIN_FILENO) == -1)
		return (0);
	(close(pipette[1]), close(pipette[0]));
	return (1);
}

char	*limit_handler(char *itterand, char *start_cmd)
{
	char	*limitter;
	char	*toadd;

	limitter = NULL;
	while (*itterand && *itterand == '<')
	{
		*itterand = '\0';
		itterand += 2;
		if (limitter != NULL)
			limitter = ft_strjoin_n_free(limitter, ft_strdup("\n"));
		toadd = file_name_trim(&itterand);
		if (toadd == NULL || *toadd == '\0')
			return (fprintf(stderr, "there aint no limitter bud ;-;\n"), 	NULL);
		limitter = ft_strjoin_n_free(limitter, toadd);
		while (*itterand == ' ')
			itterand++;
	}
	fprintf(stderr, "this is the name : %s\n", limitter);
	if (limitter == NULL)
		return (fprintf(stderr, "there aint no limitter bud ;-;\n"), NULL);
	redirect_fork(STDIN_FILENO, limitter);
	free(limitter);
	return (ft_strjoin_n_free(start_cmd, ft_strdup(itterand)));
}

char	*out_handler(char *itterand, char *start_cmd)
{
	int		fd;
	char	*file;


	*itterand++ = '\0';
	file = file_name_trim(&itterand);
	while (file != NULL)
	{
		fprintf(stderr, "this is the name : %s\n", file);
		if (file == NULL)
			return (fprintf(stderr, "there aint no file bud ;-;\n"), NULL);
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//si line too longue on peu mettre un define/cree un mod_t 00644
		free(file);
		if (fd == -1)
			return(printf("wait a minute... something aint right\n"), NULL);
		else if (dup2(fd, STDOUT_FILENO) == -1)
			return (NULL);
		close(fd);
		file = file_name_trim(&itterand);
	}
	return (ft_strjoin_n_free(start_cmd, ft_strdup(itterand)));
}

char	*in_handler(char *itterand, char *start_cmd)
{
	int		fd;
	char	*file;


	*itterand++ = '\0';
	file = file_name_trim(&itterand);
	fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
		return (fprintf(stderr, "there aint no file bud ;-;\n"), NULL);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (dup2(fd, STDIN_FILENO) == -1)
		return (NULL);
	close(fd);
	return (ft_strjoin_n_free(start_cmd, ft_strdup(itterand)));
}

char	*append_handler(char *itterand, char *start_cmd)
{
	int		fd;
	char	*file;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref


	*itterand = '\0';
	itterand += 2;
	file = file_name_trim(&itterand);
	if (file == NULL)
		return (fprintf(stderr, "there aint no file bud ;-;\n"), NULL);
	fd = open(file, O_RDWR| O_APPEND | O_CREAT, S_IRWXO);
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (dup2(fd, STDOUT_FILENO) == -1)//a voir si il faut pas utiliser STDOUT_FILENO en miniscule j'en suis presque sur
		return (NULL);
	close(fd);
	return (ft_strjoin_n_free(start_cmd, ft_strdup(itterand)));
}

t_stof	*str_to_func()
{
	t_stof	*ret;

	ret = malloc(sizeof(t_stof) * 6);
	ret[0].str = "<";
	ret[0].func = &in_handler;
	ret[1].str = ">";
	ret[1].func = &out_handler;
	ret[2].str = "<<";
	ret[2].func = &limit_handler;//ceci est a gerer
	ret[3].str = ">>";
	ret[3].func = &append_handler;
	ret[4].str = NULL;
	ret[4].func = NULL;
	return (ret);
}