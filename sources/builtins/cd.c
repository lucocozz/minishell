/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:43:34 by lucocozz          #+#    #+#             */
/*   Updated: 2021/05/21 01:57:55 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_path(const char *path)
{
	char	*new;

	if (path[0] == '~')
		new = ft_strjoin(ft_getenv("HOME"), &path[1], "");
	else if (path[0] == '.')
		new = ft_strjoin(ft_getenv("PWD"), &path[1], "");
	else if (path[0] == '-')
		new = ft_strdup(ft_getenv("OLDPWD"));
	else
		new = ft_strdup(path);
	return (new);
}

void	cd(const char *path)
{
	char		*new;
	char		*old;

	new = parse_path(path);
	if (chdir(new) != -1)
	{
		old = ft_getenv("PWD");
		ft_setenv("OLDPWD", old, 1);
		ft_setenv("PWD", new, 1);
		ft_putstr(new);
		ft_putchar('\n');
	}
	else
		ft_printf("cd: no file or directory of type: %s\n", path);
	gc_free(new);
}
