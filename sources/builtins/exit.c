/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:44:53 by lucocozz          #+#    #+#             */
/*   Updated: 2021/09/24 20:58:48 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int argc, char **argv)
{
	int	status;

	status = *get_exit_value();
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argc < 3)
	{
		if (argc == 2)
		{
			if (ft_isnumber(argv[1]) == 0)
			{
				ft_dprintf(STDERR_FILENO,
					"minishell: exit: %s: numeric argument required\n", argv[1]);
				status = 2;
			}
			else
				status = ft_atoi(argv[1]);
		}
		exit_shell(status, NULL);
	}
	ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
	return (EXIT_FAILURE);
}
