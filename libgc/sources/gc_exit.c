/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:01:22 by rotrojan          #+#    #+#             */
/*   Updated: 2021/07/18 18:01:49 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

void	gc_exit(int status, char *message)
{
	if (status == EXIT_SUCCESS && message != NULL)
		_gc_putstr_fd(STDOUT_FILENO, message);
	else if (status == EXIT_FAILURE)
	{
		_gc_putstr_fd(STDERR_FILENO, "Error: ");
		_gc_putstr_fd(STDERR_FILENO, message);
	}
	exit(status);
}
