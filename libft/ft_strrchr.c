/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:38:53 by aperol-h          #+#    #+#             */
/*   Updated: 2021/07/29 19:08:16 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*rtnval;

	rtnval = 0;
	while (1)
	{
		if (*s == (unsigned char)c)
			rtnval = (char *) s;
		if (!*s++)
			break ;
	}
	return (rtnval);
}
