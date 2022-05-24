/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 17:29:27 by aperol            #+#    #+#             */
/*   Updated: 2021/07/29 20:42:22 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static unsigned int	ft_abs(int n)
{
	int	res;

	res = n;
	if (n < 0)
		res = n * -1;
	return (res);
}

static size_t	nbr_len(int n)
{
	int	c;

	c = 0;
	while (1)
	{
		c++;
		n /= 10;
		if (ft_abs(n) <= 0)
			break ;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int		isneg;
	char	*nbr_str;
	int		i;

	isneg = 0;
	if (n < 0)
		isneg = 1;
	nbr_str = (char *)malloc((nbr_len(ft_abs(n)) + 1 + isneg) * sizeof(char));
	if (!nbr_str)
		return (NULL);
	i = 0;
	if (isneg)
		nbr_str[i++] = '-';
	while (1)
	{
		nbr_str[i++] = (ft_abs(n) % 10) + '0';
		n /= 10;
		if (ft_abs(n) <= 0)
			break ;
	}
	nbr_str[i] = '\0';
	ft_strrev(nbr_str + isneg);
	return (nbr_str);
}
