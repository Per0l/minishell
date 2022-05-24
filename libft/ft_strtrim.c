/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 12:00:40 by aperol            #+#    #+#             */
/*   Updated: 2021/07/30 16:43:19 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_in_set(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static void	calc_idx(char const *s1, char const *set, int *sidx, int *eidx)
{
	int	i;

	i = -1;
	while (s1[++i])
	{
		if (!is_in_set(s1[i], set))
			break ;
	}
	*sidx = i;
	i = ft_strlen(s1);
	while (s1[--i])
		if (!is_in_set(s1[i], set))
			break ;
	*eidx = i + 2;
	if (*eidx <= 1)
		*eidx = *sidx + 1;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		sidx;
	int		eidx;

	if (!s1 || !set)
		return (NULL);
	calc_idx(s1, set, &sidx, &eidx);
	trimmed = (char *)malloc((eidx - sidx) * sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, s1 + sidx, (eidx - sidx));
	return (trimmed);
}
