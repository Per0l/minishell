/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <aoteo-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:10:52 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/05/28 18:02:08 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Respecto al uso de envo, es lo mismo que en echo. Esto no está completo
// porque la salida debería estar ordenada por orden alfabético. 

#include "../includes/minishell.h"

void	export(int fd, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		write(fd, "declare -x ", 11);
		write(fd, __environ[i], ft_strlen(envp[i]));
		write(fd, "\n", 1);
		i++;
	}	
}
