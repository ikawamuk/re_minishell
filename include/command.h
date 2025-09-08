/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:17:42 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 15:12:19 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

#include "config.h"
#include "redirection.h"

typedef struct s_command		t_command_list;
typedef struct s_simple_cmd		t_simple_cmd;
// typedef struct s_conection_cmd	t_conection_cmd;

struct s_simple_cmd
{
	char			**argv;
	t_redir_list	*redir;
};

struct s_command
{
	t_simple_cmd		cmd;
	t_command_list		*next;
};

// union u_command
// {
// 	t_conection_cmd	connection;
// 	t_simple_cmd	simple;
// };

// struct s_command
// {
// 	enum e_cmd_type		type;
// 	union u_command		command;
// };

// struct s_conection_cmd
// {
// 	enum e_conection	connection;
// 	t_command			*presult;
// 	t_command			*next;
// };

#endif