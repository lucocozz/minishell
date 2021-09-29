/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 01:57:42 by rotrojan          #+#    #+#             */
/*   Updated: 2021/09/29 23:21:47 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# define EXIT_PERM_DENIED 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CTRL_C_VALUE 130
# define EXIT_SYNTAX_ERROR 2

typedef struct s_IO_file
{
	int	input;
	int	output;
}	t_IO_file;

enum e_pipe
{
	Output,
	Input
};

/*
** is_piped.c
*/

bool	*get_is_piped(void);
void	set_is_piped(bool value);

/*
** exec_ast.c
*/

void	exec_ast(t_node *ast, bool inline_mode);

/*
** exec_list_cmd.c
*/

void	exec_list_cmd(t_node *ast);

/*
** exec_pipe.c
*/

void	exec_pipe(t_node *ast);

/*
** exec_simple_cmd.c
*/

void	exec_simple_cmd(t_simple_cmd simple_cmd);

/*
** run_binary.c
*/

int		run_binary(char **argv);

/*
** redirections/redirection.c
*/

int		redirection(t_simple_cmd command);
void	close_redirections(t_redirection *redirection);

/*
** redirections/output_redirection.c
*/

int		output_redirection(t_redirection *redirection);

/*
** redirections/input_redirection.c
*/

int		input_redirection(t_redirection *redirection);

/*
** redirections/heredoc.c
*/

char	*heredoc(const char *delimiter);

/*
** exit_value.c
*/

int		*get_exit_value(void);
void	set_exit_value(int exit_value);
int		return_exit_value(int exit_value);

#endif
