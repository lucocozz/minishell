/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 21:29:12 by lucocozz          #+#    #+#             */
/*   Updated: 2021/10/16 17:52:19 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_redirection(char const *stream, bool input_stream_has_quotes)
{
	char	*doc;
	int		fd[2];

	doc = heredoc(stream);
	if (doc == NULL)
	{
		set_exit_value(EXIT_CTRL_C_VALUE);
		return (-1);
	}
	if (input_stream_has_quotes == false && doc != NULL)
		expand_vars_in_stream(&doc);
	if (pipe(fd) == ERR)
		exit_shell(EXIT_FAILURE, strerror(errno));
	if (doc != NULL)
		ft_putstr_fd(doc, fd[Input]);
	close(fd[Input]);
	gc_free((void **)&doc);
	return (fd[Output]);
}

int	input_redirection(char const *stream)
{
	int	fd;

	fd = open(stream, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			stream);
		set_exit_value(EXIT_FAILURE);
		return (-1);
	}
	return (fd);
}
