/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:10:52 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/10/05 18:47:16 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(t_list **var_list, char *key, char *value)
{
	t_variable	*var;
	t_list		*current;

	current = find_key(*var_list, key);
	if (current)
	{
		if (!value)
			return ;
		var = current->content;
		if (var->value)
			free(var->value);
		var->value = value;
		return ;
	}
	var = malloc(sizeof(t_variable));
	if (var == NULL)
		exit(1);
	var->key = ft_strdup(key);
	var->value = value;
	ft_lstadd_back(var_list, ft_lstnew(var));
}

int	builint_export_validator(t_list **var_list, char *arg)
{
	char	*equal;
	int		idx;
	int		i;

	i = -1;
	while (arg[++i])
	{	
		if (arg[i] == '=')
			break ;
		if ((!ft_isalnum(arg[i]) && arg[i] != '_')
			|| (i == 0 && ft_isdigit(arg[i])))
			return (ft_strerror("not a valid identifier", arg, 1));
	}
	if (i == 0)
		return (ft_strerror("not a valid identifier", arg, 1));
	equal = ft_strchr(arg, '=');
	idx = 0;
	if (!(equal == NULL || equal == arg))
	{
		idx = 1;
		*equal = '\0';
	}
	builtin_export(var_list, arg, ft_strdup(equal + idx));
	return (0);
}

int	builtin_export_parse(t_list **var_list, char **args)
{
	int	i;
	int	ret;

	if (ft_strarrlen(args) <= 1)
		return (builtin_env(*var_list, 1));
	ret = 0;
	i = 0;
	while (args[++i])
	{
		if (builint_export_validator(var_list, args[i]))
			ret = 1;
	}
	return (ret);
}

void	export_default(t_list **var_list)
{
	if (!ft_getenv(*var_list, "PWD"))
		builtin_export(var_list, "PWD", getcwd(NULL, 0));
	if (!ft_getenv(*var_list, "PATH"))
		builtin_export(var_list, "PATH",
			ft_strdup("/usr/local/bin:/usr/local/sbin:\
/usr/bin:/usr/sbin:/bin:/sbin"));
	builtin_export(var_list, "*PWD", ft_strdup(ft_getenv(*var_list, "PWD")));
	builtin_export(var_list, "OLDPWD", NULL);
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
