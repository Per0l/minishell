/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:09:07 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/07/27 18:23:24 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*working_dir;

	working_dir = malloc(MAX_BUF * sizeof(char));
	if (!working_dir)
		exit(1);
	getcwd(working_dir, MAX_BUF);
	printf("%s\n", working_dir);
	free(working_dir);
	return (0);
}
