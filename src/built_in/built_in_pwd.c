/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:15:30 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/11 11:29:14 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
		return (GEN_ERR);
	printf(YLW "%s\n" RST, path);
	free(path);
	return (SUCCESS);
}