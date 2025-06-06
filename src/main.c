/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:43:33 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/06 18:06:49 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void	tester(t_shell *shell)
{
	t_tok	*tmp;
	int i;

	tmp = shell->tok;
	i = 1;
	while(tmp)
	{
		printf("TOKEN %d\n", i++);
		printf("\tword => %s\n", tmp->word);
		printf("\ttype => %d\n", tmp->type);
		tmp = tmp->next;
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	
	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (free_all(shell), print_error(shell, MALLOC), 1);
	init_shell(shell, envp);
	while (1)
	{
		shell->input = readline(PROMPT);
		if (shell->input == NULL || ft_strcmp(shell->input, "exit") == 0)
			return (free_all(shell), printf("exit"), 0);
		else
		{
			tokenize(shell);
			expand(shell);
			tester(shell);
			add_history(shell->input);
		}
		reset_shell(shell);
	}
	free_all(shell);
}
