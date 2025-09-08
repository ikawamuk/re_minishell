/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:22:38 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/06 14:42:42 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

#include <stdlib.h>

// exit status
#define SUCCESS			0
#define SYNTAX_ERROR	2

// prompt
#define PS1	"$ "
#define PS2	"> "

// word flag
#define W_HASDOLLAR	(1 << 0) //
#define W_SINGLE_QUOTED	(1 << 1) //
#define W_DOUBLE_QUOTED	(1 << 2) //

#define W_HASQUOTEDNULL	(1 << 18) //
#define W_SAWQUOTEDNULL	(1 << 21) //

typedef enum e_token_type
{
	T_ERROR = -1,
	T_NULL = 0,
	
	T_WORD = 1,
	
	T_GREATER = 2,
	T_GREATER_GREATER = 3,
	T_LESS = 4,
	T_LESS_LESS = 5,
	
	
	T_BAR = 6,
	T_BAR_BAR = 7,
	T_AND_AND = 8,
}	t_token_type;

enum e_cmd_type
{
	SIMPLE_CMD,
	PIPE_CMD,
	OR_CMD,
	AND_CMD,
};

enum e_redir_type
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND
};

enum e_conection
{
	PIPE,
	AND,
	OR
};

#endif