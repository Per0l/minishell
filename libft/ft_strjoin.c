/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:40:41 by aperol-h          #+#    #+#             */
/*   Updated: 2022/07/28 22:18:44 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	newstr = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_memmove(newstr, s1, size1);
	ft_memmove(newstr + size1, s2, size2);
	newstr[size1 + size2] = '\0';
	return (newstr);
}

char	*ft_strljoin(char **list)
{
	size_t	i;
	char	*res;
	char	*temp;
	char	*spaced;

	i = 0;
	res = NULL;
	while (list && list[i])
	{
		if (res == NULL)
			res = list[i];
		else
		{
			spaced = ft_strjoin(res, " ");
			temp = ft_strjoin(spaced, list[i]);
			free(spaced);
			if (i > 1)
				free(res);
			res = temp;
		}
		i++;
	}
	if (i == 1)
		res = ft_strdup(res);
	return (res);
}

void	ft_free_char_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free (arr);
}

int	ft_isquoted(const char *s, int idx)
{
	int		len;
	int		i;
	int		res;

	len = (int)ft_strlen(s);
	if (idx > len || idx <= 0)
		return (0);
	i = -1;
	res = 0;
	while (++i < idx && s[i])
	{
		if (s[i] == '\'' && !(res & 2))
		{
			if (res & 1 || ft_strchr(s + i + 1, '\''))
				res ^= 1;
		}
		if (s[i] == '"' && !(res & 1))
		{
			if (res & 2 || ft_strchr(s + i + 1, '"'))
				res ^= 2;
		}
	}
	if (ft_strchr("'\"", s[i]))
		res = !((s[i] == '"' && !(res & 1)) || (s[i] == '\'' && !(res & 2)));
	return (res);
}

/* int	ft_isquoted(const char *s, int idx)
{
	int		len;
	int		i;
	int		res;

	len = (int)ft_strlen(s);
	if (idx == 0 || len - 1 == idx)
		return (0);
	i = 0;
	res = 0;
	while (++i)
	{
		if (!(res & 1) && idx + i < len && ft_strchr("'\"", s[idx + i]))
			res |= 1;
		if (!(res & 2) && idx - i >= 0 && ft_strchr("'\"", s[idx - i]))
			res |= 2;
		if (res & 1 && res & 2)
			return (1);
		if (!(idx + i < len) && !(idx - i >= 0))
			break ;
	}
	return (0);
} */