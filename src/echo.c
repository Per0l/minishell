/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <aoteo-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:37:39 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/06/08 19:31:56 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(int fd, int has_n, char *str)
{
	if (str)
		write(fd, str, ft_strlen(str));
	if (!has_n)
		write(fd, "\n", 1);
	free(str);
}

int	builtin_echo_parse(char **args)
{
	int	has_n;

	has_n = 0;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
		has_n = 1;
	if (args[1 + has_n])
		builtin_echo(1, has_n, ft_strljoin(args + 1 + has_n));
	else
		builtin_echo(1, has_n, NULL);
	return (1);
}
