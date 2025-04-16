/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:19:08 by lflayeux          #+#    #+#             */
/*   Updated: 2025/04/16 18:46:36 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char *input;
	t_signal	signals;

	(void)argc;
	(void)argv;
	(void)env;
	set_signal(&signals);
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL || ft_strcmp(input, "exit") == 0)
			return (printf("exit"),0);
		if (*input)
		{
			add_history(input);
			test_signals(signals, env);
		}
		reset_signals(&signals);
	}
}

// TESTS

void	test_signals(t_signal signals, char **env)
{
	pid_t	pid;
	char *caca[] = {"../fdfdemerde/fdf", "../test_fdf/test_maps/julia.fdf", NULL};
	int	status;
//	char *caca[] = {"/bin/bash", NULL};

	pid = fork();
	if (pid == 0)
	{
		child_signals(&signals);
		execve(caca[0], caca, env);
		printf("test");
	}
	else
	{
		parent_signals(&signals);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		{
			if (WCOREDUMP(status))
				printf("Core dump fdp\n");
		}
		status = 0;
	}
}
