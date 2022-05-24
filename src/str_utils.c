/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:26:17 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/24 16:54:06 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mem_utils.h"

size_t	ft_strlen(const char *s)
{
	int		c;

	c = 0;
	while (s[c] != 0)
		c++;
	return (c);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;

	if (n == 0)
		n = ft_strlen(s1);
	if (n == 0)
		return (1);
	while (n-- > 0)
	{
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;
		if (u1 != u2)
			return (u1 - u2);
		if (u1 == '\0')
			return (0);
	}
	return (0);
}
