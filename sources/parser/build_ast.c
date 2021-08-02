/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:59:25 by rotrojan          #+#    #+#             */
/*   Updated: 2021/08/02 16:04:04 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eat_token(t_token **tok_lst)
{
	t_token	*tmp;

	tmp = *tok_lst;
	if (*tok_lst == NULL)
		return ;
	*tok_lst = (*tok_lst)->next;
	gc_free(tmp->data);
	tmp->data = NULL;
	gc_free(tmp);
	tmp = NULL;
}

bool	build_ast(t_token **tok_lst, t_node **ast)
{
	bool	ret;

	while (*tok_lst != NULL)
	{
		if (is_logical_operator((*tok_lst)->type) == TRUE)
			ret = parse_logical_operator(tok_lst, ast);
		else if (is_pipe((*tok_lst)->type) == TRUE)
			ret = parse_pipe(tok_lst, ast);
		else if (is_leaf((*tok_lst)->type) == TRUE)
			ret = parse_simple_cmd(tok_lst, ast);
		else if ((*tok_lst)->type == Amp_tok)
			return (FALSE);
		if (ret == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
