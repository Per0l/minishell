/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:11:04 by aperol-h          #+#    #+#             */
/*   Updated: 2021/07/29 19:24:04 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*s1, const char *s2, size_t len)
{
	size_t	l2;
	size_t	l1;

	l1 = ft_strlen(s1);
	if (len > l1)
		len = l1;
	l2 = ft_strlen(s2);
	if (!l2)
		return ((char *)s1);
	while (len >= l2)
	{
		len--;
		if (!ft_memcmp(s1, s2, l2))
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
