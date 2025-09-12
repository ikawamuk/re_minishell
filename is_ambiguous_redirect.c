/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ambiguous_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:25:25 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/12 17:49:19 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parse.h"
#include <stdbool.h>

static bool	is_null_node(char *string);
static bool include_multi_word(char *string);

bool	is_ambiguous_redirect(t_redir_list *redir_list)
{
	while (redir_list)
	{
		if (redir_list->data.type != R_HEREDOC)
		{
			if (is_null_node(redir_list->data.value.file_name))
				return (true);
			if (include_multi_word(redir_list->data.value.file_name))
				return (true);
		}
	}
	return (false);
}

static bool include_multi_word(char *string)
{
	while (is_space(*string))
		string++;
	while (*string && !is_space(*string))
		string++;
	while (is_space(*string))
		string++;
	if (*string)
		return (true);
	return (false);
}

static bool	is_null_node(char *string)
{
	while (is_space(*string))
		string++;
	return (!*string);
}
