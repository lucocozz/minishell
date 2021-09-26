/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 20:07:41 by rotrojan          #+#    #+#             */
/*   Updated: 2021/09/26 02:01:29 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define REDIR_TOK_TYPE_OFFSET 5

/*
** Because of the way redirections are handled during execution, input
** redirections are added in the order they appear and output redirections are
** added in reverse order.
*/

static void	add_to_lst(t_redirection *new_redirection, t_node *simple_cmd)
{
	t_redirection	*current;

	if (new_redirection->type == Input_redir
		|| new_redirection->type == Heredoc_redir)
	{
		current = simple_cmd->content.simple_cmd.input_redir;
		if (current != NULL)
		{
			while (current->next != NULL)
				current = current->next;
			current->next = new_redirection;
		}
		else
			simple_cmd->content.simple_cmd.input_redir = new_redirection;
	}
	else
	{
		new_redirection->next = simple_cmd->content.simple_cmd.output_redir;
		simple_cmd->content.simple_cmd.output_redir = new_redirection;
	}
}

/*
** Malloc and add the redirection to the redirection linked list of the simple
** command.
*/

static bool	add_redirection(t_token **tok_lst, t_node *simple_cmd)
{
	t_redirection	*new_redir;

	if ((*tok_lst)->next == NULL)
	{
		ft_dprintf(STDERR_FILENO,
			"\nminishell: syntax error near unexpected token `newline'");
		eat_token(tok_lst);
		return (false);
	}
	new_redir = gc_malloc(sizeof(*new_redir));
	new_redir->type
		= (enum e_redirection_type)(*tok_lst)->type - REDIR_TOK_TYPE_OFFSET;
	eat_token(tok_lst);
	if ((*tok_lst)->type != Word_tok)
	{
		ft_dprintf(STDERR_FILENO,
			"\nminishell: syntax error near unexpected token `%s'",
			(*tok_lst)->data);
		return (false);
	}
	new_redir->stream = ft_strdup((*tok_lst)->data);
	new_redir->isopen = false;
	new_redir->has_quotes = (ft_strchr(new_redir->stream, '"') != NULL);
	add_to_lst(new_redir, simple_cmd);
	return (true);
}

/*
** The from_lst_to_array() function will malloc and fill the argv array of
** strings containing the arguments of the command. If a redirection is
** encountered, it will be handled by the add_redirection() function. The tokens
** of the tok_lst linked list are eaten progressivly along the process.
*/

static bool	from_lst_to_array(t_token **tok_lst, t_node *simple_cmd)
{
	int		i;

	i = 0;
	simple_cmd->content.simple_cmd.argv = gc_malloc(sizeof(char *)
			* (simple_cmd->content.simple_cmd.argc + 1));
	ft_bzero(simple_cmd->content.simple_cmd.argv,
		sizeof(simple_cmd->content.simple_cmd.argv));
	while (*tok_lst != NULL && is_leaf((*tok_lst)->type) == true)
	{
		if ((*tok_lst)->type == Word_tok)
			simple_cmd->content.simple_cmd.argv[i++]
				= ft_strdup((*tok_lst)->data);
		else if (is_redirection((*tok_lst)->type) == true)
		{
			if (add_redirection(tok_lst, simple_cmd) == false)
				return (false);
		}
		eat_token(tok_lst);
	}
	simple_cmd->content.simple_cmd.argv[i] = NULL;
	return (true);
}

/*
** The get_argc() function returns the number of arguments of the simple command
** by iterating on the tok_lst token linked list while the tokens are not
** separators. Redirection tokens are not taken in the count.
** On success, true is returned.
*/

static unsigned int	get_argc(t_token *tok_lst)
{
	unsigned int	argc;
	t_token			*current;

	argc = 0;
	current = tok_lst;
	while (current != NULL && is_leaf(current->type) == true)
	{
		if (current->type == Word_tok)
			++argc;
		else if (is_redirection(current->type) == true)
			if (current->next != NULL)
				current = current->next;
		current = current->next;
	}
	return (argc);
}

/*
** Parsing a simple command is done the following way:
** - if the token is not a leaf, it is a syntax error: false is returned;
** - the simple_command node is maloced;
** - the number of arguments of the command is obtained with get_argc();
** - from_lst_to_array() fills the argv array and the redirection linked list of
** the simple command leaf.
*/

bool	parse_simple_cmd(t_token **tok_lst, t_node **ast)
{
	t_node	*simple_cmd;

	if (is_parenthesis((*tok_lst)->type) == true)
		return (parse_parenthesis(tok_lst, ast));
	if (is_leaf((*tok_lst)->type) == false)
		return (false);
	simple_cmd = NULL;
	simple_cmd = gc_malloc(sizeof(*simple_cmd));
	ft_bzero(simple_cmd, sizeof(*simple_cmd));
	simple_cmd->type = Simple_cmd;
	simple_cmd->content.simple_cmd.argc = get_argc(*tok_lst);
	if (from_lst_to_array(tok_lst, simple_cmd) == false
		|| (*tok_lst != NULL && (*tok_lst)->type == Oparenth_tok))
	{
		gc_free((void **)&simple_cmd);
		return (false);
	}
	*ast = simple_cmd;
	return (true);
}
