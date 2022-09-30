/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:32:06 by aperol-h          #+#    #+#             */
/*   Updated: 2022/09/30 23:06:12 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	del_arg(char **args)
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
} */

void	ft_command_subsplit(t_command *command, int i)
{
	char	**new;
	char	**res;
	int		j;
	int		len;

	if (ft_countinset("\t\n\v\f\r ", command->cmd) == 0)
		return ;
	new = ft_splitcmd(command->cmd, "\t\n\v\f\r ");
	ft_strcpy(command->cmd, new[0]);
	len = (int) ft_strarrlen(command->args) + (int) ft_strarrlen(new) - 1;
	res = (char **)malloc((len + 1) * sizeof(char *));
	res[len] = NULL;
	j = -1;
	while (++j < len)
	{
		if (j > i && new[j - i])
			res[j] = ft_strdup(new[j - i]);
		else if (j > i)
			res[j] = ft_strdup(command->args[j - i + 1]);
		else
			res[j] = ft_strdup(command->args[j]);
	}
	ft_free_char_arr(command->args);
	ft_free_char_arr(new);
	command->args = res;
}

int	ft_strerror(char *error, char *sufix, int ret_err)
{
	g_ret = ret_err;
	ft_putstr_fd("minishell: ", 2);
	if (sufix)
	{
		ft_putstr_fd(sufix, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
	return (ret_err);
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

int	ft_arr_isempty(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
	{
		if (!ft_isempty(arr[i]))
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
