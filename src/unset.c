/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:48 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/08/10 18:17:26 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (ft_strarrlen(args) <= 1)
		printf("unset: not enough arguments\n");
	else
	{
		i = 1;
		while (args[i])
		{
			builtin_unset(var_list, args[i]);
			i++;
		}
	}
	return (0);
}
