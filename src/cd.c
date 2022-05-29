/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <<aoteo-be@student.42.fr> >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:54:09 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/05/27 20:48:14 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_cd(char *path)
{
	int	new_dir;

	new_dir = chdir(path);
	if (new_dir)
		printf("bash: cd: %s No existe el archivo o el directorio\n", path);
}
