/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:54:09 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/06/03 17:20:00 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char *path)
{
	int	new_dir;

	new_dir = chdir(path);
	if (new_dir)
		printf("bash: cd: %s No existe el archivo o el directorio\n", path);
	return (1);
}
