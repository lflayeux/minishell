/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:05:17 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 16:31:26 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_export(t_shell *shell, char *cmd, char **split)
{
	if (ft_get_env(shell->env, split[0]))
		shell->env = set_env(shell, split[0], shell->env, cmd);
	if (!shell->env)
		return (FALSE);
	if (ft_get_env(shell->secret, split[0]))
		shell->secret = set_env(shell, split[0], shell->secret, cmd);
	if (!shell->secret)
		return (FALSE);
	if (!ft_get_env(shell->env, split[0])
		&& ft_get_env(shell->secret, split[0]))
		shell->env = put_env(shell, shell->env, cmd);
	if (!shell->env)
		return (FALSE);
	if (!ft_get_env(shell->secret, split[0])
		&& !ft_get_env(shell->env, split[0]))
	{
		shell->env = put_env(shell, shell->env, cmd);
		shell->secret = put_env(shell, shell->secret, cmd);
		if (!shell->env | !shell->secret)
			return (FALSE);
	}
	return (TRUE);
}

void	stock_export(t_shell *shell, char *cmd)
{
	char	**split;

	if (ft_strchr(cmd, '='))
	{
		split = ft_split(cmd, '=');
		if (!split)
			free_error(shell);
		if (valid_export(shell, cmd, split) == FALSE)
		{
			ft_free_tab((void **)split);
			free_error(shell);
		}
		ft_free_tab((void **)split);
	}
	else
	{
		if (ft_get_env(shell->secret, cmd))
			shell->secret = set_env(shell, cmd, shell->secret, cmd);
		else
			shell->secret = put_env(shell, shell->secret, cmd);
		if (!shell->secret)
			free_error(shell);
	}
}

void	export_print(t_shell *shell, int i, t_exec *exec)
{
	int		j;
	char	**split;

	j = 0;
	while (shell->secret[j])
	{
		split = ft_split(shell->secret[j], '=');
		if (!split)
			free_error(shell);
		if (ft_strchr(shell->secret[j], '=') == 0)
		{
			if (!ft_get_env(shell->env, split[0]) && !is_valid_env(split[0]))
				shell->env = put_env(shell, shell->env, exec->cmd[i + 1]);
			if (!shell->env)
				return (ft_free_tab((void **)split), free_error(shell));
			printf("declare -x %s\n", split[0]);
		}
		else
			printf("declare -x %s=\"%s\"\n", split[0],
				ft_strchr(shell->secret[j], '=') + 1);
		ft_free_tab((void **)split);
		j++;
	}
}

int	exec_export(t_shell *shell, int i, t_exec *exec)
{
	if (!exec->cmd[1] || ft_strcmp(exec->cmd[1], " ") == 0)
		export_print(shell, i, exec);
	else
	{
		i++;
		while (exec->cmd[i])
		{
			if (!is_valid_env(exec->cmd[i]))
				return (print_error(exec->cmd[i], ID, shell, 1), 1);
			else
				stock_export(shell, exec->cmd[i]);
			i++;
		}
	}
	return (SUCCESS);
}
