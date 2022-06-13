/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:32:06 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/13 16:38:30 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	del_arg(char **args)
{
	int	i;

	if (!args || !args[0])
		return ;
	i = 1;
	free(args[0]);
	args[0] = NULL;
	while (args[i])
	{
		args[i - 1] = args[i];
		i++;
	}
	if (args[i - 1])
		args[i - 1] = NULL;
}
