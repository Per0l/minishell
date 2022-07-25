/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:57:37 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/07/25 18:22:58 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_list *lst)
{
	t_variable	*var;

	if (!lst)
		return (1);
	while (lst)
	{
		var = lst->content;
		if (var && var->key && ft_strcmp(var->key, "?") != 0)
			printf("%s=%s\n", var->key, var->value);
		lst = lst->next;
	}
	return (1);
}
