/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:23:26 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/01 17:14:32 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (FALSE);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_atol(const char *str, long long *out, unsigned long long res, int sign)
{
	int					i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	if ((sign == 1 && res > (unsigned long long)LONG_MAX)
		|| (sign == -1 && res > (unsigned long long)LONG_MAX + 1))
		return (0);
	*out = (long long)res * sign;
	return (1);
}

int	exec_exit(t_exec *exec, int i, int flag, t_shell *shell)
{
	long long	err;

	if (flag == 1)
		printf("exit\n");
	if (exec->cmd[i + 1])
	{
		if (!is_num(exec->cmd[i + 1]) || !ft_atol(exec->cmd[i + 1], &err, 0, 1))
		{
			printf("minishell: exit: %s: %s\n", exec->cmd[i + 1], NUM_ARG);
			if (flag == 1)
				return (free_all(shell), exit(2), GEN_ERR);
			return (GEN_ERR);
		}
		if (exec->cmd[i + 2])
			return (printf("minishell: exit: too many arguments\n"), GEN_ERR);
		err = (unsigned char)err;
		if (flag == 1)
			return (free_all(shell), exit(err), GEN_ERR);
		else
			return (err);
	}
	else if (flag == 1)
		return (free_all(shell), exit(0), SUCCESS);
	return (SUCCESS);
}
