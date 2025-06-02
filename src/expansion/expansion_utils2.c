/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:56:46 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/02 20:19:12 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_pid(t_shell **shell)
{
	int		fd;
	char	*line;
	char	**split;
	char	*pid;

	fd = open("/proc/self/status", O_RDONLY);
	if(fd == -1)
		free_exit(*shell);
	line = get_next_line(fd);
	pid = NULL;
	while (line)
	{
		if (ft_strncmp(line, "Pid:", 4) == 0)
		{
			split = ft_split(line, '\t');
			add_or_free(*shell, NULL, split, 1);
			pid = ft_strdup(ft_substr(split[1], 0, ft_strlen(split[1]) - 1));
			add_or_free(*shell, pid, NULL, 0);
			// ft_free_tab((void **)split);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (pid);
}
int	is_openquotes(char **word, int index, char quote)
{
	int	i;
	char *tmp;

	tmp = *word;
	i = 0;
	while (i < index)
	{
		if (tmp[i] == quote)
			return (0);
		i++;
	}
	return (1);
}

int	add_dollar_env(char **word, char **new_word, int *i, int *j, t_shell **shell)
{
	int		l;
	char	*var_env;

	(*j)++;
	// printf("\t\t\t\t\t\t\t\t\t%d\n", is_openquotes(word, *j,'"'));
	if ((*word)[*j] == '\0' || ((*word)[*j] == '"' && is_openquotes(word, *j,
				'"') == 0))
	{
		var_env = ft_strdup("$\0");
		// printf("\t\t\t\t\t\t\t\t\tTEST\n");
		add_or_free(*shell, var_env, NULL, 0);		
	}
	else if ((*word)[*j] == '$')
	{
		var_env = get_pid(shell);
		(*j)++;
		// printf("pid : %ld\n", ft_strlen(get_pid()));
		// (*i)++;
	}
	else if (ft_isdelim((*word)[*j], "\'\""))
		return (0);
	else
	{
		var_env = getenv(find_var_spe(*word, *j, shell));
		(*j) += strlen(find_var_spe(*word, *j, shell));
		if (!var_env)
			return (0);
	}
	// var_env = check_dollar_env(word, j, env);
	// printf("\t\t\t\t\t\tTEST: %s\n", *word);
	l = 0;
	while (var_env[l])
	{
		(*new_word)[*i] = var_env[l];
		l++;
		(*i)++;
	}
	return (0);
}
