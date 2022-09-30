/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:37:07 by aperol-h          #+#    #+#             */
/*   Updated: 2022/09/30 21:38:37 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	int		c;

	c = 0;
	while (s && s[c] != 0)
		c++;
	return (c);
}

size_t	ft_strarrlen(char **s)
{
	int		c;

	c = 0;
	while (s && s[c])
		c++;
	return (c);
}
