/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:36:59 by lucocozz          #+#    #+#             */
/*   Updated: 2021/05/01 02:35:13 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prompt(void)
{
	int			i;
	t_prompt	prompt;

	prompt.home = getenv("HOME");
	prompt.pwd = getenv("PWD");
	prompt.hostname = ft_gethostname();
	i = ft_strlen(prompt.home);
	tputs(tgetstr(BOLD_CAP, NULL), 1, ft_putchar);
	tputs(tparm(tgetstr(COLOR_CAP, NULL), COLOR_GREEN), 1, ft_putchar);
	ft_printf("%s@%s", getenv("USER"), prompt.hostname);
	tputs(tgetstr(RESET_CAP, NULL), 1, ft_putchar);
	ft_putchar(':');
	tputs(tgetstr(BOLD_CAP, NULL), 1, ft_putchar);
	tputs(tparm(tgetstr(COLOR_CAP, NULL), COLOR_BLUE), 1, ft_putchar);
	if (!ft_strncmp(prompt.home, prompt.pwd, i))
		ft_printf("~%s", &prompt.pwd[i]);
	else
		ft_printf("%s", prompt.pwd);
	tputs(tgetstr(RESET_CAP, NULL), 1, ft_putchar);
	ft_printf("> ");
	free(prompt.hostname);
}
