/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:07:42 by aperol-h          #+#    #+#             */
/*   Updated: 2021/07/30 20:03:33 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	register const unsigned char	*str1;
	register const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (n-- > 0)
	{
		if (*str1++ != *str2++)
		{
			if (str1[-1] != str2[-1])
				return (str1[-1] - str2[-1]);
		}
	}
	return (0);
}
