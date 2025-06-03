/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:09:30 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/03 15:27:30 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**init_env(char **envp)
{
	int		i;
	int		len;
	char	**env;

	len = 0;
	i = 0;
	while (envp[len])
		len++;
	env = malloc((len + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	init_shell(t_shell **shell, char **envp)
{
	(*shell)->signals = malloc(sizeof(t_signal));
	(*shell)->tok = NULL;
	(*shell)->exec = NULL;
	(*shell)->malloc = NULL;
	(*shell)->env = init_env(envp);
	(*shell)->secret = init_env(envp);	
	(*shell)->exit_code = 0;
	(*shell)->child_tab = NULL;
	(*shell)->child_index = 0;
	(*shell)->prev_fd = STDIN_FILENO;
	
}