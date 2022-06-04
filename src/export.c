/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <<aoteo-be@student.42.fr> >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:10:52 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/06/04 20:51:39 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*builtin_export(int key, char *value)
{
	t_list		*list;
	t_variable	var;

	var.key = key;
	ft_memcpy(var.value, value, ft_strlen(value)); 

	list = (t_list *) NULL;
	ft_lstadd_back(&list, ft_lstnew(&var));
	return (list);
}
