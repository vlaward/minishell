int		ft_table_size(char **table)
{
	int	i;

	i = 0;
	if (!table || !*table)
		return (0);
	while (*(table++))
		i++;
	return (i);
}
