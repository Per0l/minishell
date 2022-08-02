/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:32:06 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/02 19:16:13 by aperol-h         ###   ########.fr       */
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

void	ft_strerror(char *error, char *sufix)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	if (!sufix)
	{
		ft_putstr_fd("\n", 2);
		return ;
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(sufix, 2);
}

int	ft_isempty(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			return (0);
	}
	return (1);
}

int	ft_countinset(char *set, char *str)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str && str[++i])
	{
		if (ft_strchr(set, str[i]))
			c++;
	}
	return (c);
}
