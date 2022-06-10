/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be < aoteo-be@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:48 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/06/10 19:16:10 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	t_variable	*var;

	var = (t_variable *)content;
	var->key = NULL;
	var->value = NULL;
}

void	builtin_unset(t_list *list, char *key)
{
	t_list		*previous;
	t_variable	*var;

	previous = NULL;
	while (list->next != NULL)
	{
		var = list->content;
		if (!ft_strncmp(var->key, key, ft_strlen(key)))
		{
			if (previous)
				previous->next = list->next;
			ft_lstdelone(list, del);
			break ;
		}	
		else
		{
			previous = list;
			list = list->next;
		}	
	}
}
