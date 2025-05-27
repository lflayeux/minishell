/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:19:08 by lflayeux          #+#    #+#             */
/*   Updated: 2025/05/27 17:42:05 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ==============================================
// ================= EXPANSION ==================
// ==============================================

// RETOURNE LE PID POUR $$
char	*get_pid(void)
{
	int		fd;
	char	*line;
	char	**split;
	char	*pid;

	fd = open("/proc/self/status", O_RDONLY);
	line = get_next_line(fd);
	pid = NULL;
	while (line)
	{
		if (ft_strncmp(line, "Pid:", 4) == 0)
		{
			split = ft_split(line, '\t');
			pid = ft_strdup(ft_substr(split[1], 0, ft_strlen(split[1]) - 1));
			ft_free_tab((void **)split);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (pid);
}

int	ft_isdelim(char c, char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*find_var_spe(char *s, int index)
{
	int		i;
	char	*var;
	int		len;

	len = 0;
	while (s[index + len] && ft_isdelim(s[index + len], "|<> \'\"") != 1)
		len++;
	var = ft_calloc((len + 1), sizeof(char));
	if (!var)
		return (NULL);
	i = 0;
	while (s[index] && ft_isdelim(s[index], "|<> \'\"") != 1)
		var[i++] = s[index++];
	return (var);
}

// RETURN LE PATH POUR $ENV_VARIABLE OU NULL SI NON TROUVE
// char	*check_dollar_env(char **token, int *i, char **env)
// {
// 	int		j;
// 	char	**split;
// 	char	*path;

// 	j = 0;
// 	path = NULL;
// 	while (env[j])
// 	{
// 		split = ft_split(env[j], '=');
// 		if (ft_strcmp(split[0], find_var(*token, *i)) == 0)
// 		{
// 			path = ft_strdup(split[1]);
// 			// *i += ft_strlen(find_var(*token, *i)) + 1;
// 			*i += ft_strlen(find_var_sp(*token, *i));
// 			ft_free_tab((void **)split);
// 			return (path);
// 		}
// 		j++;
// 		ft_free_tab((void **)split);
// 	}
// 	return (*i += ft_strlen(find_var(*token, *i)), ft_strdup(""));
// }

// PERMET DE RECALCULER LA BONNE LONGUEURE EN CAS DE $
int	dollar_len(char **token, int *i, t_shell **shell)
{
	int		len;
	char	*env_path;

	len = 0;
	(void)shell;
	(*i)++;
	if ((*token)[*i] == '$')
	{
		(*i)++;
		return (ft_strlen(get_pid()));
	}
	//	else if (token[*i] == '$' &&  token[i + 1] == '?')
	else
	{
		if ((*token)[*i] == '\0' || (*token)[*i] == '"')
			return (1);
		env_path = getenv(find_var_spe(*token, *i));
		if (env_path)
			len += ft_strlen(env_path);
	}
	return (len);
}

// PERMET DE RECALCULER LA BONNE LONGUEURE EN CAS DE '' OU ""
int	quotes_len(char **token, int *i, t_shell **shell)
{
	int	len;

	len = 0;
	if ((*token)[*i] == '\'')
	{
		(*i)++;
		while ((*token)[*i] != '\'' && (*token)[*i] != '\0')
		{
			(*i)++;
			len++;
		}
		(*i)++;
	}
	else if ((*token)[*i] == '"')
	{
		(*i)++;
		while ((*token)[*i] != '"' && (*token)[*i] != '\0')
		{
			if ((*token)[*i] == '$')
				len += dollar_len(token, i, shell);
			else
			{
				// printf("%d i\n", *i);
				(*i)++;
				len++;
			}
		}
		(*i)++;
	}
	return (len);
}

// FONCTION GLOBALE POUR LE RECALCUL DES ' " et $
int	expansion_len(char **token, t_shell **shell)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while ((*token)[i])
	{
		while ((*token)[i] != '\0' && (*token)[i] != '\'' && (*token)[i] != '"'
			&& (*token)[i] != '$')
		{
			i++;
			len++;
		}
		// printf("%d iexp\n", i);
		if ((*token)[i] != '\'' || (*token)[i] != '"')
			len += quotes_len(token, &i, shell);
		if ((*token)[i] == '$')
			len += dollar_len(token, &i, shell);
	}
	return (len);
}

// ==============================================
// ================ END EXPANSION ===============
// ==============================================

// ==============================================
// =================== TESTS ====================
// ==============================================

const char	*get_token_name(int type)
{
	if (type == 0)
		return ("|");
	if (type == 1)
		return ("<");
	if (type == 2)
		return (">");
	if (type == 3)
		return ("<<");
	if (type == 4)
		return (">>");
	if (type == 5)
		return ("WORD");
	return ("error");
}

// ==============================================
// ================= FIN TESTS ==================
// ==============================================

void	execute_input(char *input, t_shell **shell)
{
	t_tok	*tmp;
	t_tok	*tmp2;
	t_tok	*tmp3;
	t_exec	*tmp4;
	int		i;
	int		past_len;
	int		new_len;
	int		j;
	int		old_j;

	(*shell)->tok = NULL;
	(*shell)->exec = NULL;
	while (*input != '\0')
	{
		tokenize(&input, &((*shell)->tok));
	}
	// ==============================================
	// ================== TOKENIZE ==================
	// ==============================================
	tmp = (*shell)->tok;
	tmp2 = (*shell)->tok;
	i = 0;
	printf("\n\n" YLW);
	printf("==============================================\n");
	printf("================== TOKENIZE ==================\n");
	printf("==============================================\n");
	printf("\n" RST);
	while (tmp != NULL)
	{
		printf("token num" RED " %d\n" RST "\ttype: %s\n"
				"\tword: %s\n",
				i++,
				get_token_name(tmp->type),
				tmp->word);
		tmp = tmp->next;
	}
	// ==============================================
	// ============== EXPANSION MALLOC ==============
	// ==============================================
	printf("\n\n" YLW);
	printf("==============================================\n");
	printf("============== EXPANSION MALLOC ==============\n");
	printf("==============================================\n");
	printf("\n" RST);
	i = 0;
	while (tmp2 != NULL)
	{
		if (tmp2->word != NULL)
		{
			past_len = ft_strlen(tmp2->word);
			new_len = expansion_len(&tmp2->word, shell);
			printf("token num" RED " %d\n" RST, i++);
			printf("============================\n");
			printf("ancien len: %d\n", past_len);
			printf("============================\n");
			printf("============================\n");
			printf("nveau len: %d\n", new_len);
			printf("============================\n");
			printf("\n");
		}
		tmp2 = tmp2->next;
	}
	// ==============================================
	// ============= EXPANSION PARSING ==============
	// ==============================================
	word_identification(shell);
	tmp3 = (*shell)->tok;
	i = 0;
	printf("\n\n" YLW);
	printf("==============================================\n");
	printf("============== EXPANSION PARSING =============\n");
	printf("==============================================\n");
	printf("\n" RST);
	while (tmp3 != NULL)
	{
		printf("token num" RED " %d\n" RST, i++);
		printf("\ttype: %s\n", get_token_name(tmp3->type));
		printf("\tword: %s\n", tmp3->word);
		tmp3 = tmp3->next;
	}
	// 	// ==============================================
	// 	// ============== EXEC BUILT_IN =================
	// 	// ==============================================
	create_lst_exec(&((*shell)->exec), &((*shell)->tok));
	tmp4 = (*shell)->exec;
	i = 0;
	printf("\n\n" YLW);
	printf("==============================================\n");
	printf("================== BUILT_IN ==================\n");
	printf("==============================================\n");
	printf("\n" RST);
	while (tmp4 != NULL)
	{
		j = 0;
		printf("exec num" RED " %d\n" RST, i++);
		printf("\tcommand:\n");
		if (tmp4->cmd)
		{
			while ((tmp4->cmd)[j])
			{
				printf("\t\tcmd num %d: %s\n", j, (tmp4->cmd)[j]);
				old_j = j;
				//  built_in(shell, &j);
				if (j == old_j)
					j++;
			}
		}
		else
			printf("\t\tcmd inexistante\n");
		printf("\tinfile:%d,   %s\n", tmp4->if_infile, tmp4->infile);
		printf("\toutfile:%d,   %s\n", tmp4->if_outfile, tmp4->outfile);
		printf("\there_doc:%d,   %s\n", tmp4->if_here_doc, tmp4->delimiter);
		printf("\tappend:%d,   %s\n", tmp4->if_append, tmp4->outfile);
		tmp4 = tmp4->pipe_to;
	}
	// ==============================================
	// ================= REAL EXEC ==================
	// ==============================================
	printf("\n\n" YLW);
	printf("==============================================\n");
	printf("==============REAL EXEC ======================\n");
	printf("==============================================\n");
	printf("\n" RST);
	// while (*input != '\0')
	// {
	// 	tokenize(&input, &((*shell)->tok));
	word_identification(shell);
	// create_lst_exec(&exec, &token);
	pipex(*shell);
	printf(YLW "\n============ FIN TEST REAL EXEC===========\n" RST);
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->signals = malloc(sizeof(t_signal));
	shell->env = init_env(envp);
	shell->secret = init_env(envp);
	(void)argc;
	(void)argv;
	//	int i = 0;
	// while (shell->env[i])
	// {
	// 	printf("%s\n", shell->env[i]);
	// 	i++;
	// }
	//========================================================================
	//========================================================================
	set_signal(shell->signals);
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL || ft_strcmp(input, "exit") == 0)
			return (printf("exit"), 0);
		if (*input)
		{
			add_history(input);
			// test_signals(signals, env);
			execute_input(input, &shell);
		}
		reset_signals(shell->signals);
	}
}
// ==============================================
// =================== TESTS ====================
// ==============================================

void	test_signals(t_signal signals, char **env)
{
	pid_t	pid;
	char	*caca[] = {"../fdfdemerde/fdf", "../test_fdf/test_maps/julia.fdf",
			NULL};
	int		status;

	// char *caca[] = {"/bin/bash", NULL};
	pid = fork();
	if (pid == 0)
	{
		child_signals(&signals);
		execve(caca[0], caca, env);
	}
	else
	{
		parent_signals(&signals);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		{
			if (WCOREDUMP(status))
				printf("Core dump fdp\n");
		}
		status = 0;
	}
}
