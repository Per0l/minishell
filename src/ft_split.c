/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:12:21 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/24 16:53:40 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mem_utils.h"
#include "str_utils.h"

unsigned int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;

	if (!dst || !src)
		return (-1);
	srclen = ft_strlen(src);
	if (srclen + 1 < size)
		ft_memmove(dst, src, srclen + 1);
	else if (size != 0)
	{
		ft_memmove(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (srclen);
}

static size_t	get_str_arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

static char	**add_str_toarr(char **arr, char const *str, size_t len, int sidx)
{
	size_t	clen;

	clen = get_str_arr_len(arr) * sizeof(*arr);
	arr = (char **)ft_realloc(arr, clen, clen + (sizeof(char *) * 2));
	if (arr == NULL)
		return (NULL);
	clen /= sizeof(*arr);
	arr[clen] = (char *)malloc((len + 1) * sizeof(char));
	if (!arr[clen])
		return (NULL);
	ft_strlcpy(arr[clen], str + sidx, len + 1);
	arr[clen + 1] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	size_t		i;
	size_t		lst_i;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *));
	if (arr == NULL)
		return (NULL);
	*arr = NULL;
	i = 0;
	lst_i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i != lst_i)
				arr = add_str_toarr(arr, s, i - lst_i, lst_i);
			lst_i = i + 1;
		}
		i++;
	}
	if (i > 0 && !(s[i - 1] == c))
		arr = add_str_toarr(arr, s, i - lst_i, lst_i);
	return (arr);
}
