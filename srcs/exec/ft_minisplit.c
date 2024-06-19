/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:06:20 by ncrombez          #+#    #+#             */
/*   Updated: 2024/06/19 16:37:53 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_to_list(char *itterand, t_list **liste)
{
	char	*start_word;
	char	chose_your_guillemet;
	char	*content;

	while (*itterand && (*itterand == ' ' || *itterand == '\n'))
		itterand++;
	if (*itterand == '\0')
		return (itterand);
	start_word = itterand;
	while (*itterand && (*itterand != ' ' && *itterand != '\n'))
	{
		if (ft_isin_table(*itterand, "\'\""))
		{
			chose_your_guillemet = *itterand;
			ft_memcpy(itterand, itterand + 1, ft_strlen(itterand));
			while (*itterand && *itterand != chose_your_guillemet)
				itterand++;
			ft_memcpy(itterand, itterand + 1, ft_strlen(itterand));
		}
		else
			itterand++;
	}
	content = ft_calloc(itterand - start_word + 1, sizeof(char));
	ft_strlcpy(content, start_word, itterand - start_word + 1);
	ft_lstadd_front(liste, ft_lstnew(content));
	return (itterand);
}

char	**ft_minisplit(char	*str)
{
	t_list	*will_be_ret;
	int		i;
	char	*itterand;
	char	**ret;

	if (!str)
		return (NULL);
	itterand = str;
	will_be_ret = NULL;
	while (*itterand != '\0')
		itterand = add_to_list(itterand, &will_be_ret);
	if (!will_be_ret)
		return (free(str), NULL);
	ret = ft_calloc(ft_lstsize(will_be_ret) + 1, sizeof(char *));
	i = -1;
	while (ft_lstnodi(&will_be_ret, ++i))
		ret[i] = ft_lstnodi(&will_be_ret, i)->content;
	ft_lstclear(&will_be_ret, NULL);
	fprintf(stderr, "voici line : %s\n", str);
	free(str);
	return (ret);//normalement y'as un fdree str
}
