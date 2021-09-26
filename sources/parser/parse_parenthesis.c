/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 00:31:23 by rotrojan          #+#    #+#             */
/*   Updated: 2021/09/26 02:20:06 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Called from the beginning of a simple command, the parse_parenthesis() will
** recursively call build_ast() and will check after it's execution if the 
** next encountered token is a closing parenthesis (that is why build_ast loops
** untill the end of the token linked list or untill a Cparenth_tok token is
** met.
*/

static bool	print_error_and_return(t_token *token)
{
	if (token == NULL)
		ft_dprintf(STDERR_FILENO,
			"\nminishell: syntax error near unexpected token `%s'", "newline");
	else
		ft_dprintf(STDERR_FILENO,
			"\nminishell: syntax error near unexpected token `%s'", token->data);
	return (false);
}

bool	parse_parenthesis(t_token **tok_lst, t_node **ast)
{
	if ((*tok_lst)->type == Cparenth_tok)
		return (print_error_and_return(*tok_lst));
	eat_token(tok_lst);
	if (*tok_lst == NULL || (*tok_lst)->type == Cparenth_tok)
		return (print_error_and_return(*tok_lst));
	if (build_ast(tok_lst, ast) == false)
		return (false);
	if (*tok_lst == NULL || (*tok_lst)->type != Cparenth_tok)
		return (false);
	eat_token(tok_lst);
	return (true);
}
