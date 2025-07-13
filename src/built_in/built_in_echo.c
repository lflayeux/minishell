/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:16:05 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 16:19:02 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo_option(t_exec *exec, int *i, int *newline)
{
	int	j;

	while (exec->cmd[*i])
	{
		if (ft_strncmp(exec->cmd[*i], "-n", 2) == 0)
		{
			j = 2;
			while (exec->cmd[*i][j] == 'n')
				j++;
			if (exec->cmd[*i][j] == '\0')
			{
				*newline = 0;
				(*i)++;
				continue ;
			}
		}
		break ;
	}
}

int	exec_echo(t_exec *exec, int i)
{
	int	newline;

	i++;
	newline = 1;
	echo_option(exec, &i, &newline);
	while (exec->cmd[i])
	{
		printf("%s", exec->cmd[i]);
		if (exec->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (FALSE);
}
