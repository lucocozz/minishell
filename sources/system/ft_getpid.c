/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:12:34 by lucocozz          #+#    #+#             */
/*   Updated: 2021/05/05 18:15:42 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_getpid(void)
{
	pid_t		pid;
	char		*pgrep;
	char		*bin_path;
	static char	*arg[] = {"pgrep", "-n", "minishell", NULL};

	bin_path = getbinpath(arg[0]);
	if (!bin_path)
		exit_shell(EXIT_FAILURE, "ft_getbinpath(): No path found.\n");
	pgrep = pipe_exec(bin_path, arg);
	pid = ft_atoi(pgrep);
	gc_free(pgrep);
	return (pid);
}