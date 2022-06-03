/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:59:21 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/06/03 17:20:06 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Simplemente con close(0) parece que funcionaría, pero no puede ser tan
// sencillo. Aquí creo que se tendrían que usar isatty, ttyname, etc., pero no
//  sé como.

#include "minishell.h"

void	builtin_exit(void)
{
	close(0);
}
