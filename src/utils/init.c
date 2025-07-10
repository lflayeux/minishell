/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:16:13 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/10 23:42:21 by pandemonium      ###   ########.fr       */
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
	if (PIPEX->child_tab)
		free(PIPEX->child_tab);
	PIPEX->child_tab = NULL;
	if (shell->var)
	{
		free(shell->var);
		shell->var = NULL;
	}
	PIPEX->prev_fd = NONE;
	// signal_global = 0;
}
void	exec_init(t_exec *node_exec)
{
	node_exec->cmd = NULL;
	node_exec->infile = NULL;
	node_exec->outfile = NULL;
	node_exec->here_doc = NULL;
	node_exec->if_infile = 0;
	node_exec->if_outfile = 0;
	node_exec->if_append = 0;
	node_exec->if_here_doc = 0;
	node_exec->pipe_to = NULL;
}
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
		// if (ft_strcmp())
		env[i] = ft_strdup(envp[i]);
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

void	get_pid(t_shell *shell)
{
	int		fd;
	char	*line;
	char	**split;
	char	*tmp;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		print_error("malloc", NULL, shell, GEN_ERR);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "Pid:", 4) == 0)
		{
			split = ft_split(line, '\t');
			if (!split)
				print_error("malloc", NULL, shell, GEN_ERR);
			tmp = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
			shell->pid = tmp;
			ft_free_tab((void **)split);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
void	init_pipex(t_shell *shell)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (print_error("malloc", NULL, shell, GEN_ERR));
	PIPEX = pipex;
	PIPEX->child_tab = NULL;
	PIPEX->child_index = 0;
	PIPEX->prev_fd = NONE;
	init_fd(shell);
}
void	init_shell(t_shell *shell, char **envp)
{
	shell->signals = malloc(sizeof(t_signal));
	set_signal(shell->signals);
	shell->tok = NULL;
	shell->exec = NULL;
	init_pipex(shell);
	shell->input = NULL;
	get_pid(shell);
	signal_global = 0;
	shell->var = NULL;
	shell->env = init_env(envp);
	shell->secret = init_env(envp);
}
