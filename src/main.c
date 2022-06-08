/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:58:39 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/08 19:19:39 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*rl_gets(void)
{
	static char	*line_read = (char *) NULL;
	char		*prompt;

	if (line_read)
	{
		free (line_read);
		line_read = (char *) NULL;
	}
	prompt = get_prompt();
	line_read = readline(prompt);
	free(prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

void	sigint_handler(int signum)
{
	if (signum == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	free_variable(void *content)
{
	t_variable	*var;

	var = (t_variable *)content;
	free(var->key);
	free(var->value);
	free(content);
}

int	main(void)
{
	char	*cmd;
	t_list	*var_list;

	var_list = NULL;
	signal(SIGINT, sigint_handler);
	while (1)
	{
		cmd = rl_gets();
		if (!cmd)
			break ;
		parse(cmd, getenv("PATH"), &var_list);
	}
	ft_lstclear(&var_list, &free_variable);
}
