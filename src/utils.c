/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:32:06 by aperol-h          #+#    #+#             */
/*   Updated: 2022/10/05 19:40:16 by aperol-h         ###   ########.fr       */
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
	int		p[2];

	if (ft_countinset("\t\n\v\f\r ", command->cmd) == 0)
		return ;
	new = ft_splitcmd(command->cmd, "\t\n\v\f\r ");
	ft_strcpy(command->cmd, new[0]);
	p[1] = (int) ft_strarrlen(command->args) + (int) ft_strarrlen(new) - 1;
	res = (char **)ft_calloc(sizeof(char *), (p[1] + 1));
	if (!res)
		exit(1);
	p[0] = -1;
	while (res && ++p[0] < p[1])
	{
		if (p[0] > i && new[p[0] - i])
			res[p[0]] = ft_strdup(new[p[0] - i]);
		else if (p[0] > i)
			res[p[0]] = ft_strdup(command->args[p[0] - i + 1]);
		else
			res[p[0]] = ft_strdup(command->args[p[0]]);
	}
	ft_free_char_arr(&command->args);
	ft_free_char_arr(&new);
	command->args = res;
}

int	ft_strerror(char *error, char *sufix, int ret_err)
{
	char	**list;
	char	*tmp;
	int		i;

	list = malloc(4 * sizeof(char *));
	if (!list)
		exit(1);
	i = -1;
	g_ret = ret_err;
	list[++i] = ft_strdup("minishell");
	if (sufix)
		list[++i] = sufix;
	list[++i] = error;
	list[++i] = NULL;
	tmp = ft_strljoin(list, ": ");
	ft_putendl_fd(tmp, 2);
	free(tmp);
	free(list[0]);
	free(list);
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
