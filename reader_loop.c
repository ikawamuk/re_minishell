/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:28:22 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/09 19:12:39 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 		set_signal_handler(void);
int			read_command(t_command_list **cmd_list, char **envp);
static int	syntax_error();
void		execute_command(t_shell *shell);

int reader_loop(t_shell *shell)
{
	while (1)
	{
		set_signal_handler();
		if (read_command(&shell->cmd_list, shell->envp)) // ctrl-Dを受け取ったら中でexitするので無限ループでいいことにしている
			shell->last_status = syntax_error();
		else
			execute_command(shell); 
			// exit when significant error occur
	}
	return (shell->last_status);
}

static void excute_command(t_shell *shell)
{
	while (shell->cmd_list)
	{
		int i = 0;
		while (shell->cmd_list->cmd.argv[i])
			printf("argv[%d]: %s\n", i, shell->cmd_list->cmd.argv[i++]);
		while (shell->cmd_list->cmd.redir_list)
		{
			printf("redir: %s\n", shell->cmd_list->cmd.redir_list->data.value);
			shell->cmd_list->cmd.redir_list = shell->cmd_list->cmd.redir_list->next;
		}
		shell->cmd_list = shell->cmd_list->next;
	}
	printf("FINISH\n");
}

static int syntax_error()
{
	printf("minishell: syntax error\n");
	return (SYNTAX_ERROR);
}
