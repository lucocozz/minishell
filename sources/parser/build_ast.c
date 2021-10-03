/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:59:25 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/03 01:15:05 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Self explanatory.
*/

bool	print_error_and_return(t_token *token)
{
	if (token == NULL)
		ft_dprintf(STDERR_FILENO,
			"\nminishell: syntax error: unexpected end of file\n");
	else
		ft_dprintf(STDERR_FILENO,
			"\nminishell: syntax error near unexpected token `%s'\n",
			token->data);
	return (false);
}

/*
** This function is used by all the parsers during the building of the AST: it
** "eats" the next token, meaning freeing the first token of the tok_lst token
** list (using gc_free from the libgc) and setting the head of tok_lst to the
** next comming token.
*/

void	eat_token(t_token **tok_lst)
{
	t_token	*tmp;

	tmp = *tok_lst;
	if (*tok_lst == NULL)
		return ;
	*tok_lst = (*tok_lst)->next;
	gc_free((void **)&tmp->data);
	gc_free((void **)&tmp);
}

/*
** Once the lexing phase is done, the token linked list is processed by the
** build_ast() function to build the Abstract Syntax Tree that will be finally
** executed in the shell loop.
** Depending on the token met in the tok_lst token linked list, the proper
** parser is called untill the tok_lst token list is empty or until a closing
** parenthesis is encountered (this is because build_ast() is recursively called
** by the parse_parenthsis() function, see parse_parenthesis.c for further
** informations.
** On success, build_ast() return true, false otherwise.
*/

bool	build_ast(t_token **tok_lst, t_node **ast)
{
	bool	ret;

	ret = true;
	while (*tok_lst != NULL && (*tok_lst)->type != Cparenth_tok)
	{
		if (is_leaf((*tok_lst)->type) == false
			&& (*tok_lst)->type != Oparenth_tok)
		{
			if (*ast == NULL)
				return (false);
			ret = parse_logical_operator(tok_lst, ast);
		}
		else
			ret = parse_pipeline(tok_lst, ast);
		if (ret == false)
			return (false);
	}
	return (true);
}
