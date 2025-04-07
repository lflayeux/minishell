/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:19:08 by lflayeux          #+#    #+#             */
/*   Updated: 2025/04/07 14:53:10 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char *input;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL || ft_strcmp(input, "exit") == 0)
			return (0);
		if (*input)
		{
			add_history(input);
		}
	}
}
