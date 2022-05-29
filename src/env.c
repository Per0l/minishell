/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <<aoteo-be@student.42.fr> >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:57:37 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/05/28 17:35:05 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// He añadido el parámetro envp que es el tercer parámetro de main, pero se podría usar también directamente __environ.
// ¿Lo considerarína como una variable global al evaluar?

#include "../includes/minishell.h"

void	builtin_env(int fd, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		write(fd, envp[i], ft_strlen(envp[i]));
		write(fd, "\n", 1);
		i++;
	}	
}
