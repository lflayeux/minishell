/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:14:23 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 13:22:38 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_cd(char **path, int i, t_shell *shell)
{
	char		*direction;
	struct stat	sb;

	direction = NULL;
	stat(path[i + 1], &sb);
	if (path[i + 1] && path[i + 2])
		return (printf("minishell: cd: too many arguments\n"), GEN_ERR);
	else if (path[i + 1] == NULL)
		direction = ft_strdup(getenv("HOME"));
	else if (path[i + 1][0] == '~')
		direction = ft_strjoin(getenv("HOME"), &path[i + 1][1]);
	else
		direction = ft_strdup(path[i + 1]);
	if (direction == NULL)
		free_error(shell);
	if (access(direction, F_OK) == -1)
		return (FREE, print_error(path[i + 1], FILE_MESS, shell, N_FOUND),
			GEN_ERR);
	else if (access(direction, F_OK | X_OK) == -1 && (!S_ISDIR(sb.st_mode)))
		return (FREE, print_error(path[i + 1], N_DIR, shell, N_FOUND), GEN_ERR);
	else if (access(direction, F_OK | X_OK) == -1)
		return (FREE, print_error(path[i + 1], PERM, shell, N_FOUND), GEN_ERR);
	chdir(direction);
	if (direction)
		free(direction);
	return (SUCCESS);
}
