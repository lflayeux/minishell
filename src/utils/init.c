/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:16:13 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 15:12:02 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_shell(t_shell *shell)
{
	if (shell->signals)
		reset_signals(shell->signals);
	if (shell->tok)
	{
		ft_lstclear_tok(shell->tok);
		shell->tok = NULL;
	}
	if (shell->input)
		free(shell->input);
	if (shell->exec)
	{
		ft_lstclear_exec(shell->exec);
		shell->exec = NULL;
	}
	if ((shell->pipex)->child_tab)
		free((shell->pipex)->child_tab);
	(shell->pipex)->child_tab = NULL;
	if (shell->var)
	{
		free(shell->var);
		shell->var = NULL;
	}
	(shell->pipex)->prev_fd = NONE;
}
char	**init_env(t_shell *shell, char **envp)
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
		return (free_error(shell), NULL);
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if(!env[i])
			return (ft_free_tab((void **)env), free_error(shell), NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	ft_check_env(char **env, char *to_check)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_check, ft_strlen(to_check)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_NULL(t_shell *shell)
{
	shell->signals = NULL;
	shell->tok = NULL;
	shell->exec = NULL;
	shell->pipex = NULL;
	shell->input = NULL;
	shell->pid = NULL;
	shell->var = NULL;
	shell->env = NULL;
	shell->secret = NULL;
}

void	init_shell(t_shell *shell, char **envp)
{
	init_NULL(shell);
	shell->signals = malloc(sizeof(t_signal));
	if(!(shell->signals))
		return (free_error(shell));
	set_signal(shell->signals);
	shell->tok = NULL;
	shell->exec = NULL;
	init_pipex(shell);
	shell->input = NULL;
	get_pid(shell);
	g_signal_global = 0;
	shell->var = NULL;
	shell->env = init_env(shell, envp);
	shell->secret = init_env(shell, envp);
}
