/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:23:43 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 19:18:37 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "config.h"

typedef struct s_redir_list    t_redir_list;
typedef struct s_redir         t_redir;

union u_redir_value
{
	char	*file_name;
	int		pipefd;
};

struct s_redir
{
	enum e_redir_type	type;
	union u_redir_value	value;
};

struct s_redir_list
{
	t_redir			data;
	t_redir_list	*next;
};

#endif