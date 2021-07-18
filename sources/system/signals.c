/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 00:28:39 by lucocozz          #+#    #+#             */
/*   Updated: 2021/07/18 04:40:29 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	ft_fprintf(STDERR_FILENO, "\n\r");
	shell();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
}

/* Self explanatory. */
void	handle_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, &sigquit_handler);
}
