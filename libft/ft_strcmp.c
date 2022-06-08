/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:27:50 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/08 19:30:35 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *p1, const char *p2)
{
	const unsigned char	*s1;
	const unsigned char	*s2;
	unsigned char		c1;
	unsigned char		c2;

	s1 = (const unsigned char *) p1;
	s2 = (const unsigned char *) p2;
	c1 = (unsigned char) *s1++;
	c2 = (unsigned char) *s2++;
	if (c1 == '\0')
		return (c1 - c2);
	while (c1 == c2)
	{
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 == '\0')
			return (c1 - c2);
	}
	return (c1 - c2);
}
