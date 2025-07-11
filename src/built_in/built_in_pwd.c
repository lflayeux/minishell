/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:15:30 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/11 15:45:29 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pwd(t_shell *shell)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
		free_error(shell);
	printf(YLW "%s\n" RST, path);
	free(path);
	return (SUCCESS);
}