/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:48 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/10/05 17:54:41 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builint_unset_validator(t_list **var_list, char *arg)
{
	int		i;

	i = -1;
	while (arg[++i])
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '_')
			|| (i == 0 && ft_isdigit(arg[i])))
			return (ft_strerror("not a valid identifier", arg, 1));
	}
	if (i == 0)
		return (ft_strerror("not a valid identifier", arg, 1));
	builtin_unset(var_list, arg);
	return (0);
}


void	builtin_unset(t_list **var_list, char *key)
{
	t_list		*previous;
	t_list		*first;
	t_variable	*var;

	previous = NULL;
	first = *var_list;
	while (*var_list != NULL)
	{
		var = (*var_list)->content;
		if (var->key && ft_strcmp(var->key, key) == 0)
		{
			if (previous)
				previous->next = (*var_list)->next;
			else
				first = (*var_list)->next;
			ft_lstdelone(*var_list, free_variable);
			*var_list = NULL;
		}	
		else
		{
			previous = *var_list;
			*var_list = (*var_list)->next;
		}	
	}
	*var_list = first;
}

int	builtin_unset_parse(t_list **var_list, char **args)
{
	int	i;
	int	ret;

	ret = 0;
	if (ft_strarrlen(args) > 1)
	{
		i = 1;
		while (args[i])
		{
			if (builint_unset_validator(var_list, args[i]))
				ret = 1;
			i++;
		}
	}
	return (ret);
}
