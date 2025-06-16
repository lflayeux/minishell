/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:03:42 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/16 18:09:30 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// ==============================================
// ================== SIGNALS ===================
// ==============================================

/**
 * @brief Handle SIGINT (Ctrl-C) in interactive mode.
 *
 * This function is called when the user presses Ctrl-C while the shell is waiting
 * for input. It clears the current line and redisplays the prompt.
 *
 * @param signal The signal number received (should be SIGINT).
 */
void	handle_ctrl_c_interactive(int signal);
/**
 * @brief Handle SIGINT (Ctrl-C) during command execution.
 *
 * This function is called when Ctrl-C is pressed while a command is running.
 * It simply prints a newline to keep the shell output clean.
 *
 * @param signal The signal number received (should be SIGINT).
 */
void	handle_ctrl_c_action(int signal);
/**
 * @brief Handle SIGQUIT (Ctrl-\) signal.
 *
 * This function is called when the user presses Ctrl-\. It clears the current
 * input line, but does not redisplay the prompt, leaving the output clean.
 *
 * @param signal The signal number received (should be SIGQUIT).
 */
void	handle_ctrl_dump(int signal);
/**
 * @brief Set default signal handlers for the interactive shell.
 *
 * Initializes the signal actions for `SIGINT` (Ctrl-C) and `SIGQUIT` (Ctrl-\).
 * - `SIGINT`: calls `handle_ctrl_c_interactive` to cleanly reset the prompt.
 * - `SIGQUIT`: is ignored.
 *
 * @param signals A pointer to the `t_signal` structure to configure.
 */
void	set_signal(t_signal *signals);
/**
 * @brief Update signal handler for the parent process after forking.
 *
 * Sets `SIGINT` (Ctrl-C) to call `handle_ctrl_c_action`, allowing the parent
 * to remain responsive while a child process runs.
 *
 * @param signals A pointer to the `t_signal` structure already configured.
 */
void	parent_signals(t_signal *signals);
/**
 * @brief Set default behavior for signals in the child process.
 *
 * Resets `SIGQUIT` (Ctrl-\) to its default behavior (`SIG_DFL`), allowing
 * the child process to terminate normally when receiving this signal.
 *
 * @param signals A pointer to the `t_signal` structure already configured.
 */
void	child_signals(t_signal *signals);
/**
 * @brief Restore the default signal behavior for the interactive shell.
 *
 * Used after a command execution or subprocess finishes to reset the
 * signal handlers to interactive mode:
 * - `SIGINT`: handled by `handle_ctrl_c_interactive`
 * - `SIGQUIT`: ignored
 *
 * @param signals A pointer to the `t_signal` structure already configured.
 */
void	reset_signals(t_signal *signals);


#endif