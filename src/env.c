/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:57:37 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/06/03 17:39:50 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// He añadido el parámetro envp que es el tercer parámetro de main, pero se
// podría usar también directamente __environ. ¿Lo consideraran como una
// variable global al evaluar? porque solo se puede usar una.

#include "minishell.h"

int	builtin_env(void)
{
	int	i;

	i = 0;
	while (__environ[i])
	{
		write(1, __environ[i], ft_strlen(__environ[i]));
		write(1, "\n", 1);
		i++;
	}	
	return (1);
}
