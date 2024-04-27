/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:06:20 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/17 15:32:52 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_to_list(char *itterand, t_list **liste)
{
	char	*start_word;
	char	chose_your_guillemet;
	char	*content;

	while (*itterand && *itterand == ' ')
		itterand++;
	start_word = itterand;
	while (*itterand && *itterand != ' ')
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

	itterand = str;
	will_be_ret = NULL;
	while (*itterand != '\0')
		itterand = add_to_list(itterand, &will_be_ret);
	ret = ft_calloc(ft_lstsize(will_be_ret) + 1, sizeof(char *));
	i = 0;
	while (ft_lstnodi(&will_be_ret, i))
		ret[i++] = ft_lstnodi(&will_be_ret, i)->content;
	ft_lstclear(&will_be_ret, NULL);
	return (free(str), ret);
}
