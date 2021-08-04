/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 00:28:39 by lucocozz          #+#    #+#             */
/*   Updated: 2021/08/04 02:37:25 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_signal_on(void)
{
	static int	signal_on = 0;

	return (&signal_on);
}

static void	sigint_handler(int sig)
{
	int	*signal_on;

	signal_on = get_signal_on();
	*signal_on = sig;
}

static void	sigwinch_handler(int sig)
{
	int	*signal_on;

	signal_on = get_signal_on();
	*signal_on = sig;
}

/* Self explanatory. */
void	handle_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGWINCH, &sigwinch_handler);
}
