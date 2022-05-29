/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <<aoteo-be@student.42.fr> >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:59:21 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/05/28 18:14:28 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// Simplemente con close(0) parece que funcionaría, pero no puede ser tan sencillo.
// Aquí creo que se tendrían que usar isatty, ttyname, etc., pero no sé como.

#include "../includes/minishell.h"

void	builtin_exit(void)
{
  close(0);
}
