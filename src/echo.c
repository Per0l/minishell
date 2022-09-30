/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:37:39 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/09/29 23:07:46 by aperol-h         ###   ########.fr       */
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

int	builtin_echo_args(char **args)
{
	int	i;
	int	j;
	int	has_n;

	i = 0;
	has_n = 0;
	while (args && args[++i])
	{
		if (ft_strlen(args[i]) < 2)
			break ;
		if (args[i][0] != '-')
			break ;
		j = 0;
		while (args[i] && args[i][++j])
			if (args[i][j] != 'n')
				break ;
		if (j != (int)ft_strlen(args[i]))
			break ;
		has_n++;
		args[i][0] = '\0';
	}
	return (has_n);
}

int	builtin_echo_parse(char **args)
{
	int	has_n;

	has_n = builtin_echo_args(args);
	if (args[1 + has_n])
		builtin_echo(1, has_n, ft_strljoin(args + 1 + has_n, " "));
	else
		builtin_echo(1, has_n, NULL);
	return (0);
}
