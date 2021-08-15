/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 00:30:31 by rotrojan          #+#    #+#             */
/*   Updated: 2021/08/12 18:52:02 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** A pipeline is made of at least one simple command. If a pipe token is found
** after a first command, parse_pipeline() will loop on the following steps
** as long as the next coming token is not a pipe:
** - the pipe token is eaten;
** - if the token linked list is empty, it is an error: FALSE is returned;
** - the pipe node in malloced and initialized;
** - the AST is transfered to the left part of the pipe_node and the
** parse_simple_cmd() function is called on the right child of the pipe_node.
** On success, TRUE is returned.
*/

bool	parse_pipeline(t_token **tok_lst, t_node **ast)
{
	t_node	*pipe_node;
	t_node	*simple_cmd;

	if (parse_simple_cmd(tok_lst, &simple_cmd) == FALSE)
		return (FALSE);
	*ast = simple_cmd;
	while (*tok_lst != NULL && (*tok_lst)->type == Pipe_tok)
	{
		eat_token(tok_lst);
		if (*tok_lst == NULL)
			return (FALSE);
		pipe_node = NULL;
		pipe_node = gc_malloc(sizeof(*pipe_node));
		ft_bzero(pipe_node, sizeof(*pipe_node));
		pipe_node->type = Pipe_node;
		pipe_node->content.child.left = *ast;
		*ast = pipe_node;
		if (parse_simple_cmd(tok_lst, &((*ast)->content.child.right)) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}