/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:01:22 by rotrojan          #+#    #+#             */
/*   Updated: 2021/05/02 15:24:01 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *str_error, t_garbage_lst **garbage_lst)
{
	int				ret;
	t_garbage_lst	*current_garbage;
	t_garbage_lst	*next_garbage;

	current_garbage = *garbage_lst;
	if (str_error == NULL)
	{
		ft_printf("Exit minishell\n");
		ret = EXIT_SUCCESS;
	}
	else
	{
		ft_printf("Error: %s\n", str_error);
		ret = EXIT_FAILURE;
	}
	while (current_garbage)
	{
		next_garbage = current_garbage->next;
		free(current_garbage->garbage_ptr);
		current_garbage->garbage_ptr = NULL;
		free(current_garbage);
		current_garbage = NULL;
		current_garbage = next_garbage;
	}
	exit(ret);
}
