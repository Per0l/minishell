/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 17:56:48 by aperol-h          #+#    #+#             */
/*   Updated: 2021/07/30 22:12:21 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*firsts;
	char		*firstd;
	const char	*lasts;
	char		*lastd;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		firsts = (const char *) src;
		firstd = (char *) dest;
		while (n--)
			*firstd++ = *firsts++;
	}
	else
	{
		lasts = (const char *)src + (n - 1);
		lastd = (char *)dest + (n - 1);
		while (n--)
			*lastd-- = *lasts--;
	}
	return (dest);
}
