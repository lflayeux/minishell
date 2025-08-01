/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:23:26 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/01 16:47:10 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	is_num(char *str)
{
	int	i = 0;

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

int	ft_atoll(const char *str, long long *out)
{
	int			i = 0;
	int			sign = 1;
	long long	res = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		int	digit = str[i++] - '0';

		if (res > (LLONG_MAX - digit) / 10)
			return (0);
		res = res * 10 + digit;
	}
	if (str[i] != '\0')
		return (0);
	*out = res * sign;
	return (1);
}

int	exec_exit(t_exec *exec, int i, int flag, t_shell *shell)
{
	long long	code;

	if (flag == 1)
		printf("exit\n");
	if (exec->cmd[i + 1])
	{
		if (!is_num(exec->cmd[i + 1]) || !ft_atoll(exec->cmd[i + 1], &code))
		{
			printf("minishell: exit: %s: %s\n", exec->cmd[i + 1], NUM_ARG);
			if (flag == 1)
				free_all(shell), exit(2);
			return (GEN_ERR);
		}
		if (exec->cmd[i + 2])
			return (printf("minishell: exit: too many arguments\n"), GEN_ERR);
		code = (unsigned char)code;
		if (flag == 1)
			return (free_all(shell), exit(code), GEN_ERR);
		else
			return (code);
	}
	else if (flag == 1)
		return (free_all(shell), exit(0), SUCCESS);
	return (SUCCESS);
}
