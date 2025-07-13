/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:02:54 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 17:48:57 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>

# define SUCCESS 0
# define GEN_ERR 1
# define BUILTIN_ERROR 2
# define CMD_EXEC 126
# define N_FOUND 127
# define EXIT_ARG 128
# define CTRL_C 130
# define CTRL_D 137

# define N_CMD_MESS "command not found"
# define FILE_MESS "No such file or directory"
# define PARSE_MESS "syntax error near unexpected token"
# define N_DIR "Not a directory"
# define PERM "Permissions denied"
# define ID "not a valid identifier"

void	print_error(char *s1, char *s2, t_shell *shell, int type);
int		parse_error(t_shell *shell, t_tok **error);

#endif