/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:59:21 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/10/05 18:00:47 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_numeric(char *str)
{
	int						i;
	unsigned long long int	c;

	i = -1;
	c = -1;
	while (str && str[++i])
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
			continue ;
		else if (!ft_isdigit(str[i]))
			return (0);
		if ((int)c == -1)
			c = 0;
		c *= 10;
		c += str[i] - '0';
		if (c - (str[0] == '-' && c > 0) > LLONG_MAX)
			return (0);
	}
	c -= (str[0] == '-' && c > 0);
	if (i == 0)
		return (0);
	return (c <= LLONG_MAX);
}

int	builtin_exit(char **args)
{
	size_t	argv;
	char	*str;

	argv = ft_strarrlen(args);
	if (argv == 1)
		exit(0);
	str = ft_strtrim(args[1], "\t\n\v\f\r ");
	if (!ft_is_numeric(str))
	{
		free(str);
		exit(ft_strerror("numeric argument required", args[1], 255));
	}
	free(str);
	if (argv != 2)
		return (ft_strerror("too many arguments", NULL, 1));
	exit(ft_atoi(args[1]));
}
