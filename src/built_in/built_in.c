/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:33:18 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/11 00:10:39 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	built_in(t_exec *exec, t_shell *shell, int flag)
{
	if (!exec->cmd || exec->cmd[0] == NULL)
	{
		signal_global = 1;
		return (FALSE);
	}
	if (!(ft_strcmp(exec->cmd[0], "echo")))
		signal_global = exec_echo(exec, 0);
	else if (ft_strcmp(exec->cmd[0], "cd") == 0)
		signal_global = exec_cd(exec->cmd, 0, shell);
	else if (ft_strcmp(exec->cmd[0], "pwd") == 0)
		signal_global = exec_pwd();
	else if (ft_strcmp(exec->cmd[0], "env") == 0)
		signal_global = exec_env(shell, 0, exec);
	else if (ft_strcmp(exec->cmd[0], "export") == 0)
		signal_global = exec_export(shell, 0, exec);
	else if (ft_strcmp(exec->cmd[0], "unset") == 0)
		signal_global = exec_unset(shell, 0, exec);
	else
		return (FALSE);
	if (flag == 0)
	{
		free_all(shell);
		exit(signal_global);
	}
	return (TRUE);
}
