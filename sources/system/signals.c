/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 00:28:39 by lucocozz          #+#    #+#             */
/*   Updated: 2021/05/06 00:40:13 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	exit_shell(EXIT_SUCCESS, "\n");
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	exit_shell(EXIT_SUCCESS, "\n");
}

void	handle_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, &sigquit_handler);
}