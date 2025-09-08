/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:03:34 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/06 14:23:48 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_shell	init_minishell(void);
int				reader_loop(t_shell *shell);

int minishell(void)
{
	t_shell	shell;

	shell = init_minishell();
	reader_loop(&shell);

	return (shell.last_status);
}

static t_shell init_minishell(void)
{
	t_shell	shell;

	shell.last_status = INITIAL_STATUS;
	shell.cmd_list = NULL;
	return (shell);
}
