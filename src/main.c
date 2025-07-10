/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:43:33 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/10 23:42:21 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			signal_global = 0;

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

// void	expand_tok(t_shell *shell)
// {
// 	expand(shell);
// 	new_prompt(shell);
// 	tokenize(shell);
// }
void	tester(t_shell *shell)
{
	t_tok	*tmp_tok1;
	t_tok	*tmp2_tok2;
	t_exec	*tmp_exec;
	int		i;
	int		j;

	tmp_tok1 = shell->tok;
	i = 1;
	printf("\n" RED "============================" RST "\n");
	printf("" RED "========== DEBUG ===========" RST "\n");
	printf("" RED "============================" RST "\n");
	while (tmp_tok1)
	{
		printf("TOKEN %d\n", i++);
		printf("\tword\t\t===> %s\n", tmp_tok1->word);
		if (tmp_tok1->word)
			printf("\tlen_word\t===> %ld\n", ft_strlen(tmp_tok1->word));
		printf("\ttype\t\t===> %s\n", get_token_name(tmp_tok1->type));
		tmp_tok1 = tmp_tok1->next;
	}
	if (expand(shell) == FALSE)
		return ;
	tmp2_tok2 = shell->tok;
	printf("\n" RED "============================" RST "\n");
	printf("" RED "====== AFTER EXPANSE =======" RST "\n");
	printf("" RED "============================" RST "\n");
	i = 1;
	while (tmp2_tok2)
	{
		printf("TOKEN %d\n", i++);
		printf("\tword\t\t===> %s\n", tmp2_tok2->word);
		if (tmp2_tok2->word)
			printf("\tlen_word\t===> %ld\n", ft_strlen(tmp2_tok2->word));
		printf("\ttype\t\t===> %s\n", get_token_name(tmp2_tok2->type));
		tmp2_tok2 = tmp2_tok2->next;
	}
	if (create_lst_exec(shell) == 0)
		return ;
	printf("\n" RED "============================" RST "\n");
	printf("" RED "= AFTER EXEC_LIST CREATION =" RST "\n");
	printf("" RED "============================" RST "\n");
	tmp_exec = shell->exec;
	i = 1;
	while (tmp_exec)
	{
		j = 0;
		printf("EXEC %d\n", i++);
		if (tmp_exec->cmd)
		{
			printf("\tcmd\t\t===> ");
			while (tmp_exec->cmd[j])
				printf("%s ", tmp_exec->cmd[j++]);
			printf("\n");
		}
		if (tmp_exec->infile)
			printf("\tinfile\t\t===> %s\n", tmp_exec->infile);
		if (tmp_exec->outfile)
			printf("\toutfile\t\t===> %s\n", tmp_exec->outfile);
		if (tmp_exec->if_here_doc == 1)
		{
			j = 0;
			printf("\there_doc\t\t===> ");
			while (tmp_exec->here_doc && tmp_exec->here_doc[j])
				printf("%s ", tmp_exec->here_doc[j++]);
			printf("\n");
		}
		tmp_exec = tmp_exec->pipe_to;
	}
	printf("\n" RED "============================" RST "\n");
	printf("" RED "========== EXEC ============" RST "\n");
	printf("" RED "============================" RST "\n");
	printf("\n\n");
	pipex(shell);
	printf("\n\n");
}
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (free_all(shell), print_error("malloc", NULL, shell, GEN_ERR),
			1);
	init_shell(shell, envp);
	while (1)
	{
		shell->input = readline(PROMPT);
		if (shell->input == NULL || ft_strcmp(shell->input, "exit") == 0)
			return (free_all(shell), printf("exit"), 0);
		else
		{
			add_history(shell->input);
			tokenize(shell);
			// expand(shell);
			tester(shell);
		}
		reset_shell(shell);
	}
	free_all(shell);
}
