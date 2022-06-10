/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <aoteo-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:10:52 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/06/08 19:02:56 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(t_list **var_list, char *key, char *value)
{
	t_variable	*var;

	var = malloc(sizeof(t_variable));
	if (var == NULL)
		exit(1);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	if (var_list == NULL)
		*var_list = ft_lstnew(var);
	else
		ft_lstadd_back(var_list, ft_lstnew(var));
}

int	builtin_export_parse(t_list **var_list, char **args)
{
	char	**exp_args;
	char	*joined_args;

	joined_args = ft_strljoin(args + 1);
	if (joined_args == NULL)
		return (1);
	exp_args = ft_split(joined_args, '=');
	if (exp_args == NULL)
		exit(1);
	free(joined_args);
	if (ft_strarrlen(exp_args) >= 2)
		builtin_export(var_list, exp_args[0], exp_args[1]);
	ft_free_char_arr(exp_args);
	return (1);
}
