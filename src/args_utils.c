/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:32:06 by aperol-h          #+#    #+#             */
/*   Updated: 2022/07/25 13:59:45 by user             ###   ########.fr       */
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

char	*join_env(char *key, char *value)
{
	char	*res;
	char	*tmp;

	res = ft_strjoin(key, "=");
	if (res == NULL)
		exit(1);
	tmp = ft_strjoin(res, value);
	if (tmp == NULL)
		exit(1);
	free(res);
	return (tmp);
}
