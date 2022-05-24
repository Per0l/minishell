/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 17:53:40 by aperol            #+#    #+#             */
/*   Updated: 2021/07/29 21:03:26 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		strlen;
	char	*new;
	int		i;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	new = (char *)malloc((strlen + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < strlen)
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
