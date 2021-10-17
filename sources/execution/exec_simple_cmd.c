/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 02:27:14 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/17 17:38:31 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_simple_cmd command, t_IO_file save)
{
	int	ret;

	ret = run_binary(command.argv);
	close(save.input);
	close(save.output);
	exit(ret);
}

static void	catch_signals(int sig)
{
	int			*signum;
	const char	*sig_list[32] = {
		[SIGINT] = "\n",
		[SIGSEGV] = "Segmentation fault\n",
		[SIGBUS] = "Bus error\n",
		[SIGABRT] = "Aborted\n",
		[SIGQUIT] = "Quit\n",
		[SIGTERM] = "Terminated\n",
		[SIGTRAP] = "Trace/breakpoint trap\n",
		[SIGPIPE] = ""
	};

	signum = get_signum();
	if (sig == SIGINT)
		*signum = SIGINT;
	if (sig_list[sig] != NULL)
		ft_dprintf(STDERR_FILENO, "%s", sig_list[sig]);
	set_exit_value(sig + 128);
}

static void	parent(int pid)
{
	int		status;

	signal(SIGQUIT, SIG_IGN);
	ignore_signals();
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	if (WIFSIGNALED(status))
		catch_signals(WTERMSIG(status));
	if (WIFEXITED(status))
		set_exit_value(WEXITSTATUS(status));
}

static void	close_io(t_IO_file save)
{
	dup2(save.input, STDIN_FILENO);
	dup2(save.output, STDOUT_FILENO);
	close(save.input);
	close(save.output);
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
			child(command, save);
		else
			parent(pid);
	}
	close_io(save);
}
