/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:23:49 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 17:53:29 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include "command.h"

typedef struct s_shell
{
	int				last_status;
	t_command_list	*cmd_list;
	char		**envp;
}	t_shell;

#endif