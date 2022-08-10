/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:59:21 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/08/10 20:20:09 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = -1;
	str = ft_strtrim(str, "\t\n\v\f\r ");
	while (str && str[++i])
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
			continue ;
		else if (!ft_isdigit(str[i]))
		{
			free(str);
			return (0);
		}
	}
	free(str);
	return (1);
}

int	builtin_exit(char **args, int is_parent)
{
	size_t	argv;

	argv = ft_strarrlen(args);
	if (is_parent)
		ft_putendl_fd("exit", 2);
	if (argv == 1)
		exit(0);
	if (!ft_is_numeric(args[1]))
		exit(ft_strerror("numeric argument required", args[1], 2));
	if (argv != 2)
		return (ft_strerror("too many arguments", NULL, 1));
	exit(ft_atoi(args[1]));
}
