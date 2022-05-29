/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/29 18:19:17 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *cmd, char *path)
{
	char	**args;
	char	*executable;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (i == 0)
		{
			executable = search_executable(ft_split(path, ':'), args[i]);
			if (executable)
			{
				printf("%s\n", executable);
				free(executable);
			}
			else
				printf("minishell: command not found: %s\n", args[i]);
		}
		free(args[i]);
		i++;
	}
	free(args);
}
