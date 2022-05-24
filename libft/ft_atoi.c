/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:04:04 by aperol-h          #+#    #+#             */
/*   Updated: 2021/07/30 18:07:22 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define FT_ULONG_MAX ((unsigned long)(~0L))

static long int	ft_strtol(const char *string, char **endPtr, int base)
{
	const char		*p;
	long			result;
	unsigned long	restmp;

	p = string;
	while (ft_isspace((unsigned char)(*p)))
		p += 1;
	if (*p == '-')
	{
		p += 1;
		restmp = ft_strtoul(p, endPtr, base);
		if (restmp == FT_ULONG_MAX)
			restmp = 0;
		result = -(restmp);
	}
	else
	{
		if (*p == '+')
			p += 1;
		result = ft_strtoul(p, endPtr, base);
	}
	if ((result == 0) && (endPtr != 0) && (*endPtr == p))
		*endPtr = (char *) string;
	return (result);
}

int	ft_atoi(const char *nptr)
{
	return ((int)ft_strtol(nptr, (char **) NULL, 10));
}
