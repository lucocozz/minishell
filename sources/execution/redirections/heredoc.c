/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:32:38 by lucocozz          #+#    #+#             */
/*   Updated: 2021/10/02 21:20:10 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_input(char **doc, char *line)
{
	char	*tmp;

	tmp = *doc;
	if (tmp == NULL)
		*doc = ft_strdup(line);
	else
		*doc = ft_strjoin(tmp, line, "\n");
	gc_free((void **)&tmp);
}

char	*heredoc(const char *delimiter)
{
	char	*line;
	char	*doc;
	t_term	*term;

	doc = NULL;
	line = NULL;
	term = set_termios();
	reset_history_data();
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = input();
		reset_history_data();
		if (line == NULL)
			line = ft_strdup("\n");
		else if (ft_strcmp(line, delimiter) == 0)
			break ;
		append_input(&doc, line);
		gc_free((void **)&line);
		ft_putstr_fd("\r\n", STDERR_FILENO);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term->saved);
	ft_putchar_fd('\n', STDERR_FILENO);
	append_input(&doc, NULL);
	return (doc);
}
