/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:05:41 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 18:33:48 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "parse.h"

size_t	count_word_list_node(t_word_list *list)
{
	size_t	count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}

void	*free_word_list(t_word_list *list)
{
	t_word_list	*next;

	while (list)
	{
		next = list->next;
		free(list->data.value);
		free(list);
		list = next;
	}
	return (NULL);
}

void **free_2darr(void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

int	error_create_argv(t_simple_cmd *cmd, t_word_list *list)
{
	list = free_word_list(list);
	cmd->argv = free_2darr((void **)cmd->argv);
	return (ERROR);
}

int create_argv(t_simple_cmd *cmd, t_word_list *list)
{
	t_word_list *next;
	size_t	len;
	size_t	i;

	if (!list)
		return (NO_ERROR);
	len = count_word_list_node(list);
	cmd->argv = calloc(len + 1, sizeof(char *));
	if (!cmd->argv)	
		return (ERROR);
	i = 0;
	while (i < len)
	{
		next = list->next;
		cmd->argv[i] = strdup(list->data.value);
		if (!cmd->argv[i])
			return (error_create_argv(cmd, list));
		free(list->data.value);
		free(list);
		list = next;
		i++;
	}
	return (NO_ERROR);
}

void *free_redirect_list(t_redir_list *list)
{
	t_redir_list	*next;

	while (list)
	{
		next = list->next;
		free(list->redir.file_name);
		free(list->redir.heredoc_eof);
		free(list);
		list = next;
	}
	return (NULL);
}

void	*free_rword_list(t_redir_word_list *list)
{
	t_redir_word_list	*next;

	while (list)
	{
		next = list->next;
		free(list->data.rword.value);
		free(list);
		list = next;
	}
	return (NULL);
}

int error_create_redirect_list(t_simple_cmd *cmd, t_redir_word_list *rword_list)
{
	cmd->redir = free_redirect_list(cmd->redir);
	rword_list = free_rword_list(rword_list);
	return (ERROR);
}

int	set_redirect_word(t_simple_cmd *cmd, t_redir_word_list *rword_list)
{
	if (cmd->redir->redir.type != R_HEREDOC)
	{
		cmd->redir->redir.file_name = strdup(rword_list->data.rword.value);
		if (!cmd->redir->redir.file_name)
			return (error_create_redirect_list(cmd, rword_list));
	}
	else  if (cmd->redir->redir.type == R_HEREDOC)
	{
		cmd->redir->redir.heredoc_eof = strdup(rword_list->data.rword.value);
		if (!cmd->redir->redir.heredoc_eof)
			return (error_create_redirect_list(cmd, rword_list));
		gather_heredoc(&cmd->redir->redir); // make tmp file, read stdin, write in, unlink tmp file set fd as the ->file name 
	}
	return (NO_ERROR);
}

int create_redirect_list(t_simple_cmd *cmd, t_redir_word_list *rword_list)
{
	t_redir_word_list	*next_word;
	t_redir_list		*next_node;

	if (!rword_list)
		return (NO_ERROR);
	while (rword_list)
	{
		next_node = cmd->redir->next;
		next_word = rword_list->next;
		cmd->redir->redir.type = rword_list->data.type;
		if (set_redirect_word(cmd, rword_list) != NO_ERROR)
			return (ERROR);
		cmd->redir = next_node;
		free(rword_list->data.rword.value);
		free(rword_list);
		rword_list = next_word;
	}
	return (NO_ERROR);
}


int create_command(t_simple_cmd *cmd, t_element element)
{
	int result;

	cmd->argv = NULL;
	cmd->redir = NULL;
	result = create_argv(cmd, element.word_list);
	if (result != NO_ERROR)
		return (ERROR);
	result = create_redirect_list(cmd, element.rword_list);
	if (result != NO_ERROR)
	{
		cmd->argv = free_2darr(cmd->argv); 
		return (ERROR);
	}
	return (NO_ERROR);
}
