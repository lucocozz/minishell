/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:38:02 by lucocozz          #+#    #+#             */
/*   Updated: 2021/05/24 19:30:00 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Core of program */
void	shell(void)
{
	char	*line;

	while (1)
	{
		prompt();
		line = input();
		if (line[0] != '\0')
			put_in_history(line);
		else
			gc_free(line);
		ft_fprintf(STDERR_FILENO, "\n\r");
	}
}
