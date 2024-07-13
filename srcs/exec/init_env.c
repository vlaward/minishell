#define MIN_ENV_SIZE 3
#include "../../includes/minishell.h"

char	**env_from_scratch()//Changer les free pars les nouvelles fonctrionsa de la libft que je vais rajkouter. rajouter les perror
{
	char	**ret;
	char	*cwd;
	char	*tmp;

	cwd = (char *)ft_calloc(PATH_MAX, sizeof(char ));
	if (!getcwd(cwd, PATH_MAX))
		return (NULL);
	ret = (char**)ft_calloc(MIN_ENV_SIZE + 1, sizeof(char *));
	if (!ret)
		return (perror("malloc"), NULL);
	ret[3] = NULL;
	ret[0] = ft_strjoin("PWD=", cwd);
	if (!ret[0])
		return(free(ret[1]), free(ret), free(cwd), NULL) ;
	ret[1] = ft_strdup("SHLVL=1");
	if (!ret[1])
		return(free(ret), free(cwd), NULL) ;
	tmp = ft_strjoin("_=", cwd);
	if (!tmp)
		return(free(ret[1]), free(ret[0]), free(ret), free(cwd), NULL) ;
	ret[2] = ft_strjoin(tmp, "/./minishell");
	if (!ret[2])
		return(free(ret[1]), free(ret[0]), free(ret), free(cwd), free(tmp), NULL);//trop long mais ca reduiras avec les nouveau free
	return (ret);
	}

char	*shlvl_increment(char	*env)//J'aime pas faire de si petites fonctyions mais je crois que c'est plus clair comme ca
{
	char	*nbr;
	char	*ret;

	nbr = ft_itoa(ft_atoi(env + 6) + 1);
	if (!nbr)
		return (NULL);
	ret = ft_strjoin("SHLVL=", nbr);
	return (free(nbr), ret);
}


char **init_env(char **env)//changer le compteur de "size" du tableau pour une fonction de la libft que je ais rajouter 
{
	char	**ret;
	char	**tmp;

	if (!env || !*env)
		return (env_from_scratch());
	ret = (char**)ft_calloc(ft_table_size(env) + 1, sizeof(char *));
	if (!ret)
	 	return (perror("malloc"), NULL);
	tmp = ret;
	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 5) == 0)
			*(ret) = shlvl_increment(*(env++));
		else
			*(ret) = ft_strdup(*(env++));
		if (!*(ret++))
			return (perror("malloc"), NULL);//<===============================FREE THE FUCKING TABLE DON'T YOU FORGET U SUCKER (of course use tmp 'caus you ain't dumb)
	}
	*ret = NULL;//don';t know if it's uselfull knowing full ass I used calloc that init evrything at 0. Still think it's usefull
	return (tmp);
}
