/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:29:02 by aperol-h          #+#    #+#             */
/*   Updated: 2021/07/30 18:06:56 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define FT_ULONG_MAX ((unsigned long)(~0L))

static void	base_stroul(int *base, int c)
{
	if (*base == 0)
	{
		if (c == '0')
			*base = 8;
		else
			*base = 10;
	}
}

static void	pre_strtoul(int *c, int *neg, int *base, const char *s)
{
	while (1)
	{
		*c = *s++;
		if (!ft_isspace(*c))
			break ;
	}
	if (*c == '-')
	{
		*neg = 1;
		*c = *s++;
	}
	else if (*c == '+')
		*c = *s++;
	if ((*base == 0 || *base == 16)
		&& *c == '0' && (*s == 'x' || *s == 'X'))
	{
		*c = s[1];
		s += 2;
		*base = 16;
	}
	base_stroul(base, *c);
}

static void	overflow_stroul(int *any, unsigned long *acc, int base, int c)
{
	unsigned long	cutoff;
	int				cutlim;

	cutoff = (unsigned long)FT_ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)FT_ULONG_MAX % (unsigned long)base;
	if (*any < 0 || *acc > cutoff || (*acc == cutoff && c > cutlim))
		*any = -1;
	else
	{
		*any = 1;
		*acc *= base;
		*acc += c;
	}
}

static void	main_stroul(const char *s, int *any, unsigned long *acc, int base)
{
	int		c;

	while (1)
	{
		c = *s++;
		if (ft_isdigit(c))
			c -= '0';
		else if (ft_isalpha(c))
		{
			if (c >= 'A' && c <= 'Z')
				c -= 'A' - 10;
			else
				c -= 'a' - 10;
		}
		else
			break ;
		if (c >= base)
			break ;
		overflow_stroul(any, acc, base, c);
	}
}

unsigned long	ft_strtoul(const char *nptr, char **endptr, int base)
{
	const char		*s;
	unsigned long	acc;
	int				c;
	int				neg;
	int				any;

	s = nptr;
	neg = 0;
	pre_strtoul(&c, &neg, &base, s);
	acc = 0;
	any = 0;
	main_stroul(s, &any, &acc, base);
	if (any < 0)
		acc = FT_ULONG_MAX;
	else if (neg)
		acc = -acc;
	if (endptr != 0)
	{
		if (any)
			*endptr = (char *)s - 1;
		else
			*endptr = (char *)nptr;
	}
	return (acc);
}
