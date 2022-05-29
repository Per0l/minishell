/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <<aoteo-be@student.42.fr> >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:37:39 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/05/27 16:27:10 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// He añadido el parámetro fd pensando en que se puede redireccionrr la salida a un fichero

#include "../includes/minishell.h"

void	builtin_echo(int fd, int has_n, char *str)
{
	write(fd, str, ft_strlen(str));
	if (!has_n)
		write(fd, "\n", 1);
}
