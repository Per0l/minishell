/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:27:12 by aperol-h          #+#    #+#             */
/*   Updated: 2022/10/03 20:22:39 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_str_toarr(char **arr, char const *str, size_t len, int sidx)
{
	size_t	clen;

	clen = ft_strarrlen(arr) * sizeof(*arr);
	arr = (char **)ft_realloc(arr, clen, clen + (sizeof(char *) * 2));
	if (arr == NULL)
		return (NULL);
	clen /= sizeof(*arr);
	arr[clen] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!arr[clen])
		return (NULL);
	if (len > 0)
		ft_strlcpy(arr[clen], str + sidx, len + 1);
	arr[clen + 1] = NULL;
	return (arr);
}

char	**ft_splitcmd(char const *s, char *set)
{
	char		**arr;
	size_t		i;
	size_t		lst_i;

	if (!s || ft_strlen(s) == 0)
		return (NULL);
	arr = ft_calloc(1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = -1;
	lst_i = 0;
	while (s[++i])
	{
		if (!ft_strchr(set, s[i]) || ft_isquoted(s, i))
			continue ;
		if (i != lst_i)
			arr = add_str_toarr(arr, s, i - lst_i, lst_i);
		lst_i = i + 1;
	}
	if (arr && i > 0 && !ft_strchr(set, s[i - 1]))
		arr = add_str_toarr(arr, s, i - lst_i, lst_i);
	if (arr && (ft_strchr("|", s[i - 1]) || ft_strchr("|", s[0])))
		ft_free_char_arr(&arr);
	return (arr);
}

int	is_builtin(char *arg)
{
	return ((ft_strcmp(arg, "cd") == 0)
		|| (ft_strcmp(arg, "export") == 0)
		|| (ft_strcmp(arg, "unset") == 0)
		|| (ft_strcmp(arg, "exit") == 0)
		|| (ft_strcmp(arg, "echo") == 0)
		|| (ft_strcmp(arg, "pwd") == 0)
		|| (ft_strcmp(arg, "env") == 0));
}
