/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:16:13 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/07 13:38:21 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_shell(t_shell *shell)
{
	if (shell->tok)
	{
		ft_lstclear_tok(shell->tok);
		shell->tok = NULL;
	}
	if (shell->var)
	{
		free(shell->var);
		shell->var = NULL;
	}
	if (shell->input)
		free(shell->input);
	if (shell->signals)
		reset_signals(shell->signals);
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
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int ft_check_env(char **env, char *to_check)
{
    int i;

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

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		print_error(shell, MALLOC);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "Pid:", 4) == 0)
		{
			split = ft_split(line, '\t');
			if (!split)
				print_error(shell, MALLOC);
			shell->pid = ft_strdup(ft_substr(split[1], 0, ft_strlen(split[1]) - 1));
			ft_free_tab((void **)split);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
void	init_shell(t_shell *shell, char **envp)
{
	(void)envp;
	shell->signals = malloc(sizeof(t_signal));
	set_signal(shell->signals);
	shell->tok = NULL;
	shell->input = NULL;
	get_pid(shell);
	shell->error = 0;
	shell->var = NULL;
	shell->env = init_env(envp);
}
