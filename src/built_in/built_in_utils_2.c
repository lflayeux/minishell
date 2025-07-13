/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:40:35 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 20:42:13 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_env(char *exec)
{
	int	i;

	i = 0;
	if (!exec || (!ft_isalpha(exec[0]) && exec[0] != '_'))
		return (0);
	while (exec[i] && exec[i] != '=')
	{
		if (!ft_isalnum(exec[i]) && exec[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
