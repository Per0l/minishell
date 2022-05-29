/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:58:39 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/28 18:02:36 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#ifndef MAX_BUF
# define MAX_BUF 200
#endif

char	*get_prompt(void)
{
	char	path[MAX_BUF];
	char	*user;
	char	*prompt;
	int		user_len;
	int		path_len;

	getcwd(path, MAX_BUF);
	user = getenv("USER");
	user_len = ft_strlen(user);
	path_len = ft_strlen(path);
	prompt = (char *)malloc((user_len + path_len + 4) * sizeof(char));
	if (!prompt)
		exit(1);
	ft_memmove(prompt, user, user_len);
	ft_memmove(prompt + user_len, ":", 1);
	ft_memmove(prompt + user_len + 1, path, path_len);
	ft_memmove(prompt + user_len + 1 + path_len, "$ ", 2);
	*(prompt + user_len + path_len + 3) = 0;
	return (prompt);
}

char	*rl_gets(char *prompt)
{
	static char	*line_read = (char *) NULL;

	if (line_read)
	{
		free (line_read);
		line_read = (char *) NULL;
	}
	line_read = readline(prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

void	sigint_handler(int signum)
{
	char	*prompt;

	if (signum == 2)
	{
		prompt = get_prompt();
		printf("\n%s", prompt);
		free(prompt);
	}
}

int	main(void)
{
	char	*prompt;
	char	*cmd;

	signal(SIGINT, sigint_handler);
	prompt = get_prompt();
	while (1)
	{
		cmd = rl_gets(prompt);
		if (!cmd)
			break ;
		parse(cmd);
	}
	free(prompt);
}
