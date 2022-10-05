/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:54:09 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/10/05 18:50:58 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_list *lst, char *path)
{
	char	*pwd;
	char	*tmp;

	builtin_export(&lst, "OLDPWD", ft_strdup(ft_getenv(lst, "PWD")));
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_strerror(strerror(errno), "getcwd", 1);
		pwd = ft_getenv(lst, "*PWD");
		tmp = malloc((ft_strlen(pwd) + 2) * sizeof(char));
		ft_strcpy(tmp, pwd);
		tmp[ft_strlen(pwd)] = '/';
		tmp[ft_strlen(pwd) + 1] = '\0';
		pwd = ft_strjoin(tmp, path);
		free(tmp);
	}
	builtin_export(&lst, "PWD", pwd);
	builtin_export(&lst, "*PWD", ft_strdup(ft_getenv(lst, "PWD")));
}

int	builtin_cd(t_list *lst, char **args)
{
	int		new_dir;
	char	*path;
	char	*tmp;

	path = args[1];
	if (!path)
		path = ft_getenv(lst, "HOME");
	if (!path)
		return (ft_strerror("HOME not set", "cd", 1));
	new_dir = chdir(path);
	if (new_dir)
	{
		tmp = ft_strjoin("cd: ", path);
		ft_strerror(strerror(errno), tmp, 1);
		free(tmp);
		return (1);
	}
	else
		update_pwd(lst, path);
	return (0);
}
