/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:09:09 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 15:31:33 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H


#include "config.h"
#include "token.h"

// return value (result)
enum e_return_value
{
	NO_ERROR = 0,
	ERROR = 1,
	CMD_FINISH = -1,
};

typedef struct s_parse_info
{
	const char		*str;
	size_t			str_i;
	t_token_type	prev_token;
}	t_parse_info;

#endif