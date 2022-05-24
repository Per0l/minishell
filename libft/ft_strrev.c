/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 17:46:43 by aperol            #+#    #+#             */
/*   Updated: 2021/07/29 21:38:27 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	size_t	i;
	size_t	strlen;
	char	tmp;

	strlen = ft_strlen(str);
	i = 0;
	while (i < strlen / 2)
	{
		tmp = str[i];
		str[i] = str[strlen - i - 1];
		str[strlen - i - 1] = tmp;
		i++;
	}
}
