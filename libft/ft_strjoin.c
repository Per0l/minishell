/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:40:41 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/03 17:34:20 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	newstr = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_memmove(newstr, s1, size1);
	ft_memmove(newstr + size1, s2, size2);
	newstr[size1 + size2] = '\0';
	return (newstr);
}

char	*ft_strljoin(char **list)
{
	size_t	i;
	char	*res;
	char	*temp;
	char	*spaced;

	i = 0;
	res = NULL;
	while (list && list[i])
	{
		if (res == NULL)
			res = list[i];
		else
		{
			spaced = ft_strjoin(res, " ");
			temp = ft_strjoin(spaced, list[i]);
			free(spaced);
			if (i > 1)
				free(res);
			res = temp;
		}
		i++;
	}
	if (i == 1)
		res = ft_strdup(res);
	return (res);
}
