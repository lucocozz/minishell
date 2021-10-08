/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 02:27:14 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/08 17:24:44 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_simple_cmd command)
{
	int	ret;

	ret = run_binary(command.argv);
	if (ret == EXIT_PERM_DENIED)
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
			command.argv[0], strerror(errno));
	else if (ret == EXIT_CMD_NOT_FOUND)
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			command.argv[0]);
	exit(ret);
}

static void	parent(void)
{
	int		*sig;
	int		status;

	sig = get_signal_on();
	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			*sig = SIGINT;
			ft_putchar_fd('\n', STDERR_FILENO);
			set_exit_value(EXIT_CTRL_C_VALUE);
		}
		else if (WTERMSIG(status) == SIGSEGV)
		{
			ft_dprintf(STDERR_FILENO, "Segmentation fault (core dumped)\n");
			set_exit_value(EXIT_SEGFAULT);
		}
	}
	if (WIFEXITED(status))
		set_exit_value(WEXITSTATUS(status));
}

static void	close_io(t_IO_file save, t_simple_cmd command)
{
	dup2(save.input, STDIN_FILENO);
	dup2(save.output, STDOUT_FILENO);
	close(save.input);
	close(save.output);
	if (command.fd_in != STDIN_FILENO)
		close(command.fd_in);
	if (command.fd_out != STDOUT_FILENO)
		close(command.fd_out);
}

void	exec_simple_cmd(t_simple_cmd command)
{
	pid_t		pid;
	t_IO_file	save;

	save.input = dup(STDIN_FILENO);
	save.output = dup(STDOUT_FILENO);
	dup2(command.fd_in, STDIN_FILENO);
	dup2(command.fd_out, STDOUT_FILENO);
	if (command.argv[0] != NULL && command.argv[0][0] != '\0'
		&& run_builtin(get_len_array(command.argv), command.argv)
		== EXIT_CMD_NOT_FOUND)
	{
		pid = fork();
		if (pid == ERR)
			exit_shell(EXIT_FAILURE, strerror(errno));
		else if (pid == 0)
			child(command);
		else
			parent();
	}
	close_io(save, command);
}
