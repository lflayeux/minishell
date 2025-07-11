/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:21:47 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/11 15:17:52 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_env(t_shell *shell, char *cmd, char ***tmp)
{
	char	**split;

	split = ft_split(cmd, '=');
	if (!split)
		free_error(shell);
	if (GET_ENV(shell->env, split[0]) == 1)
	{
		*tmp = set_env(split[0], *tmp, cmd);
		if (*tmp == NULL)
			return (free_error(shell), ft_free_tab((void **)split));
		ft_free_tab((void **)split);
		return ;
	}
	else
	{
		*tmp = put_env(shell, *tmp, cmd);
		if (*tmp == NULL)
			return (free_error(shell), ft_free_tab((void **)split));
	}
	ft_free_tab((void **)split);
}
int	exec_env(t_shell *shell, int i, t_exec *exec)
{
	int		j;
	char	**tmp;

	tmp = init_env(shell->env);
	if (!tmp)
		free_error(shell);
	while (exec->cmd[i + 1])
	{
		if (ft_strchr(exec->cmd[i + 1], '='))
			check_env(shell, exec->cmd[i + 1], &tmp);
		else
			return (ft_free_tab((void **)tmp), 1);
		i++;
	}
	j = 0;
	while (tmp[j])
		printf("%s\n", tmp[j++]);
	return (ft_free_tab((void **)tmp), SUCCESS);
}
