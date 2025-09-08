/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:23:43 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/01 19:07:46 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "config.h"

typedef struct s_redir_list    t_redir_list;
typedef struct s_redir         t_redir;

struct s_redir
{
	enum e_redir_type	type;
	char				*file_name;
	char				*heredoc_eof;
};

struct s_redir_list
{
	t_redir			redir;
	t_redir_list	*next;
};

#endif