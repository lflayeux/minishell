/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:43:33 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/07 00:58:29 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tester(t_shell *shell)
{
	t_tok	*tmp;
	t_tok	*tmp2;
	int i;

	tmp = shell->tok;
	i = 1;
	while(tmp)
	{
		printf("TOKEN %d\n", i++);
		printf("\tword => %s\n", tmp->word);
		if (tmp->word)
			printf("\tlen_word => %ld\n", ft_strlen(tmp->word));
		printf("\ttype => %d\n", tmp->type);
		tmp = tmp->next;
	}
	expand(shell);
	tmp2 = shell->tok;
	while(tmp2)
	{
		printf("TOKEN %d\n", i++);
		printf("\tword => %s\n", tmp2->word);
		if (tmp2->word)
			printf("\tlen_word => %ld\n", ft_strlen(tmp2->word));
		printf("\ttype => %d\n", tmp2->type);
		tmp2 = tmp2->next;
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
			//expand(shell);
			tester(shell);
			add_history(shell->input);
		}
		reset_shell(shell);
	}
	free_all(shell);
}
