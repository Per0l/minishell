/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:13:14 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/24 16:52:29 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	register const char	*firsts;
	register char		*firstd;
	register const char	*lasts;
	register char		*lastd;

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

void	*ft_realloc(void *ptr, size_t ori_size, size_t size)
{
	void	*new;

	if (!ptr)
	{
		new = malloc(size);
		if (!new)
			return (NULL);
	}
	else
	{
		if (ori_size < size)
		{
			new = malloc(size);
			if (!new)
				return (NULL);
			ft_memmove(new, ptr, ori_size);
			free(ptr);
		}
		else
			new = ptr;
	}
	return (new);
}
