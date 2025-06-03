/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:19:08 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/03 14:43:23 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const char	*get_token_name(int type);
void	test_signals(t_signal signals, char **env);

void	execute_input(char *input, t_shell **shell);


int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	rl_initialize();
	shell = malloc(sizeof(t_shell));
	init_shell(&shell, envp);
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
			ft_free_all(shell);
			printf("%s", shell->tok->word);
		}
		reset_signals(shell->signals);
		
	}
	clear_history();
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
void	execute_input(char *input, t_shell **shell)
{
	t_tok	*tmp;
	t_exec	*tmp4;
	int		i;
	int		past_len;
	int		new_len;

	while (*input != '\0')
	{
		tokenize(&input, &((*shell)->tok), *shell);
	}
	tmp = (*shell)->tok;

	while (tmp != NULL)
	{
		if (tmp->word != NULL)
		{
			past_len = ft_strlen(tmp->word);
			new_len = expansion_len(&tmp->word, shell);
		}
		tmp = tmp->next;
	}
	word_identification(shell);
	create_lst_exec(*shell);
	tmp4 = (*shell)->exec;
	i = 0;
	while (tmp4 != NULL)
	{
		if (tmp4->cmd)
		{
			while ((tmp4->cmd)[i])
			{
				built_in(shell, &i);
				i++;
			}
		}
		tmp4 = tmp4->pipe_to;
	}
	pipex(*shell);
}

// void	execute_input(char *input, t_shell **shell)
// {
// 	t_tok	*tmp;
// 	t_tok	*tmp2;
// 	t_tok	*tmp3;
// 	t_exec	*tmp4;
// 	int		i;
// 	int		past_len;
// 	int		new_len;
// 	int		j;
// 	int		old_j;

// 	while (*input != '\0')
// 	{
// 		tokenize(&input, &((*shell)->tok), *shell);
// 	}
// 	// ==============================================
// 	// ================== TOKENIZE ==================
// 	// ==============================================
// 	tmp = (*shell)->tok;
// 	tmp2 = (*shell)->tok;
// 	i = 0;
// 	printf("\n\n" YLW);
// 	printf("==============================================\n");
// 	printf("================== TOKENIZE ==================\n");
// 	printf("==============================================\n");
// 	printf("\n" RST);
// 	while (tmp != NULL)
// 	{
// 		printf("token num" RED " %d\n" RST "\ttype: %s\n"
// 				"\tword: %s\n",
// 				i++,
// 				get_token_name(tmp->type),
// 				tmp->word);
// 		tmp = tmp->next;
// 	}
// 	// ==============================================
// 	// ============== EXPANSION MALLOC ==============
// 	// ==============================================
// 	printf("\n\n" YLW);
// 	printf("==============================================\n");
// 	printf("============== EXPANSION MALLOC ==============\n");
// 	printf("==============================================\n");
// 	printf("\n" RST);
// 	i = 0;
// 	while (tmp2 != NULL)
// 	{
// 		if (tmp2->word != NULL)
// 		{
// 			past_len = ft_strlen(tmp2->word);
// 			new_len = expansion_len(&tmp2->word, shell);
// 			printf("token num" RED " %d\n" RST, i++);
// 			printf("============================\n");
// 			printf("ancien len: %d\n", past_len);
// 			printf("============================\n");
// 			printf("============================\n");
// 			printf("nveau len: %d\n", new_len);
// 			printf("============================\n");
// 			printf("\n");
// 		}
// 		tmp2 = tmp2->next;
// 	}
// 	// ==============================================
// 	// ============= EXPANSION PARSING ==============
// 	// ==============================================
// 	word_identification(shell);
// 	tmp3 = (*shell)->tok;
// 	i = 0;
// 	printf("\n\n" YLW);
// 	printf("==============================================\n");
// 	printf("============== EXPANSION PARSING =============\n");
// 	printf("==============================================\n");
// 	printf("\n" RST);
// 	while (tmp3 != NULL)
// 	{
// 		printf("token num" RED " %d\n" RST, i++);
// 		printf("\ttype: %s\n", get_token_name(tmp3->type));
// 		printf("\tword: %s\n", tmp3->word);
// 		tmp3 = tmp3->next;
// 	}
// 	// 	// ==============================================
// 	// 	// ============== EXEC BUILT_IN =================
// 	// 	// ==============================================
// 	create_lst_exec(*shell);
// 	tmp4 = (*shell)->exec;
// 	i = 0;
// 	printf("\n\n" YLW);
// 	printf("==============================================\n");
// 	printf("================== BUILT_IN ==================\n");
// 	printf("==============================================\n");
// 	printf("\n" RST);
// 	while (tmp4 != NULL)
// 	{
// 		j = 0;
// 		printf("exec num" RED " %d\n" RST, i++);
// 		printf("\tcommand:\n");
// 		if (tmp4->cmd)
// 		{
// 			while ((tmp4->cmd)[j])
// 			{
// 				printf("\t\tcmd num %d: %s\n", j, (tmp4->cmd)[j]);
// 				old_j = j;
// 				// built_in(shell, &j);
// 				if (j == old_j)
// 					j++;
// 			}
// 		}
// 		else
// 			printf("\t\tcmd inexistante\n");
// 		// printf("\t\t\t\t\t\t\t\t\t\t\tTEST\n");
// 		printf("\tinfile:%d,   %s\n", tmp4->if_infile, tmp4->infile);
// 		printf("\toutfile:%d,   %s\n", tmp4->if_outfile, tmp4->outfile);
// 		printf("\there_doc:%d,   %s\n", tmp4->if_here_doc, tmp4->delimiter);
// 		printf("\tappend:%d,   %s\n", tmp4->if_append, tmp4->outfile);
// 		tmp4 = tmp4->pipe_to;
// 	}
// 	// ==============================================
// 	// ================= REAL EXEC ==================
// 	// ==============================================
// 	printf("\n\n" YLW);
// 	printf("==============================================\n");
// 	printf("==============REAL EXEC ======================\n");
// 	printf("==============================================\n");
// 	printf("\n" RST);
// 	// while (*input != '\0')
// 	// {
// 	// 	tokenize(&input, &((*shell)->tok));
// 	word_identification(shell);
// 	// create_lst_exec(&exec, &token);
// 	pipex(*shell);
// 	printf(YLW "\n============ FIN TEST REAL EXEC===========\n" RST);

// 	// ==============================================
// 	// ================= LST MALLOC ==================
// 	// ==============================================
// 	printf("\n\n" YLW);
// 	printf("==============================================\n");
// 	printf("==============LST MALLOC ======================\n");
// 	printf("==============================================\n");
// 	printf("\n" RST);
// 	t_malloc *tmp5;
// 	tmp5 = (*shell)->malloc;
// 	if(!tmp5)
// 		printf("Ya rien a free en fait chef\n");
// 	// i = 0;
// 	while (tmp5 != NULL)
// 	{
// 		// printf("malloc num" RED " %d\n" RST, i++);
// 		printf("\tcommand:\n");
// 		if (tmp5->tab)
// 		{
// 			j = 0;
// 			while ((tmp5->tab)[j])
// 			{
// 				printf("\t\ttab_str num:%d: %s\n", j, (tmp5->tab)[j]);
// 				j++;
// 			}
// 		}
// 		if (tmp5->str)
// 			printf("\t\tstr is: %s\n", (tmp5->str));
// 		tmp5 = tmp5->next;
// 	}

// 	printf(YLW "\n============ FIN LST MALLOC===========\n" RST);

// }