/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:02:54 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/17 18:49:20 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

struct s_shell;

//# define MALLOC 0
typedef enum e_error_type
{
	MALLOC,
	SYNTAX_PIPE,
	SYNTAX_END,

}							ERROR_TYPE;

void    print_error(t_shell *shell, ERROR_TYPE err);
int     parse_error(t_shell *shell);

#endif