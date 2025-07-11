/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:21:47 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/11 11:29:08 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_env(t_shell *shell, char *cmd, char ***tmp)
{
	char	**split;

	split = ft_split(cmd, '=');
	if (!split)
		return ;
	if (GET_ENV(shell->env, split[0]) == 1)
	{
		*tmp = set_env(split[0], *tmp, cmd);
		ft_free_tab((void **)split);
		return ;
	}
	else
		*tmp = put_env(shell, *tmp, cmd);
	ft_free_tab((void **)split);
}
int	exec_env(t_shell *shell, int i, t_exec *exec)
{
	int		j;
	char	**tmp;

	tmp = init_env(shell->env);
	while (exec->cmd[i + 1])
	{
		if (ft_strchr(exec->cmd[i + 1], '='))
			check_env(shell, exec->cmd[i + 1], &tmp);
		else
		{
			ft_free_tab((void **)tmp);
			return (print_error(exec->cmd[i + 1], FILE_MESS, shell, 1), 1);
			break ;
		}
		i++;
	}
	j = 0;
	while (tmp[j])
		printf("%s\n", tmp[j++]);
	return (ft_free_tab((void **)tmp), SUCCESS);
}
