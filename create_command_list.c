/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:05:41 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/09 19:21:05 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

static void	*free_word_list(t_word_list *list)
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
	cmd->argv = (char **)free_2darr((void **)cmd->argv);
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

static void *free_redirect_list(t_redir_list *list)
{
	t_redir_list	*next;

	while (list)
	{
		next = list->next;
		if (list->data.type != R_HEREDOC)
			free(list->data.value.file_name);
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
	cmd->redir_list = free_redirect_list(cmd->redir_list);
	rword_list = free_rword_list(rword_list);
	return (ERROR);
}


// いずれのタイプも
int	make_new_data(t_redir *new_data, t_redir_word_list *rword_list)
{
	new_data->type = rword_list->data.type;
	if (rword_list->data.type != R_HEREDOC)
	{
		new_data->value.file_name = strdup(rword_list->data.rword.value);
		if (!new_data->value.file_name)
			return (ERROR);
	}
	// else  if (cmd->redir->redir.type == R_HEREDOC) // word_list->data.rword.valueがEOF
	// {
	//	new_data->value.file_name = NULL; free()してもいいようにNULLにしておく。
	// 	// rword_list->data.pipe にpipefdをセット
	// 	if (gather_heredoc(&cmd->redir->redir, rword_list->data.rword) == ERROR); // make tmp file, read stdin, write in, unlink tmp file set fd as the ->file name 
	// 		return (error_create_redirect_list(cmd, rword_list));
	// }
	return (NO_ERROR);
}

int push_redirect_list(t_simple_cmd *cmd, t_redir new_data);

int create_redirect_list(t_simple_cmd *cmd, t_redir_word_list *rword_list)
{
	t_redir_word_list	*next_word;
	t_redir				new_data;

	if (!rword_list)
		return (NO_ERROR);
	while (rword_list)
	{
		next_word = rword_list->next;
		if (make_new_data(&new_data, rword_list) == ERROR)
			return (free_redirect_list(cmd->redir_list), ERROR);
		if (push_redirect_list(cmd, new_data) == ERROR)
			return (free_redirect_list(cmd->redir_list), free(new_data.value.file_name), ERROR);
		free(rword_list->data.rword.value);
		free(rword_list);
		rword_list = next_word;
	}
	return (NO_ERROR);
}

int push_redirect_list(t_simple_cmd *cmd, t_redir new_data)
{
	t_redir_list	*node;
	t_redir_list	*tail;

	node = malloc(sizeof(t_redir_list));
	if (!node)
		return (ERROR);
	node->next = NULL;
	node->data.type = new_data.type;
	node->data.value.file_name = new_data.value.file_name;
	if (!node->data.value.file_name)
		return (free(node), ERROR);
	if (!cmd->redir_list)
		cmd->redir_list = node;
	else
	{
		tail = cmd->redir_list;
		while (tail->next)
			tail = tail->next;
		tail->next = node;
	}
	return (NO_ERROR);
}

void *free_simple_command(t_simple_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	cmd->argv = (char **)free_2darr((void *)cmd->argv);
	cmd->redir_list = free_redirect_list(cmd->redir_list);
	return (NULL);
}

void *free_command_list(t_command_list *cmd)
{
	t_command_list	*next;

	while (cmd)
	{
		next = cmd->next;
		free_simple_command(&cmd->cmd);
		free(cmd);
		cmd = next;
	}
	return (NULL);
}


void free_element(t_element element)
{
	t_word_list			*next_w;
	t_redir_word_list	*next_r;

	while (element.word_list)
	{
		next_w = element.word_list->next;
		free(element.word_list->data.value);
		free(element.word_list);
		element.word_list = next_w;
	}
	while (element.rword_list)
	{
		next_r = element.rword_list->next;
		free(element.rword_list->data.rword.value);
		free(element.rword_list);
		element.rword_list = next_r;
	}
	return ;
}

void	*free_element_list(t_element_list *list)
{
	t_element_list	*next;

	while (list)
	{
		next = list->next;
		free_element(list->data);
		free(list);
		list = next;
	}
	return (NULL);
}

int error_create_command_list(t_command_list **cmd_list, t_element_list *element_list)
{
	*cmd_list = free_command_list(*cmd_list);
	element_list = free_element_list(element_list);
	return (ERROR);
}

int create_command(t_simple_cmd *cmd, t_element element)
{
	int result;

	cmd->argv = NULL;
	cmd->redir_list = NULL;
	
	
	result = create_argv(cmd, element.word_list);
	if (result != NO_ERROR)
		return (ERROR);
	result = create_redirect_list(cmd, element.rword_list);
	if (result != NO_ERROR)
	{
		cmd->argv = (char **)free_2darr((void **)cmd->argv); 
		return (ERROR);
	}
	return (NO_ERROR);
}


int push_command(t_command_list **cmd_list, t_simple_cmd *cmd)
{
	t_command_list *new;
	t_command_list *tail;

	if (!cmd_list || !cmd)
		return (ERROR);
	new = malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->cmd = *cmd;
	new->next = NULL;
	cmd->argv = NULL;
	cmd->redir_list = NULL;
	if (!*cmd_list)
	{
		*cmd_list = new;
		return (NO_ERROR);
	}
	tail = *cmd_list;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	return (NO_ERROR);
}

int create_command_list(t_command_list **cmd_list, t_element_list *element_list) // cmd_list の所有権あり
{
	int result;
	t_simple_cmd	cmd;
	t_element_list	*next;

	*cmd_list = NULL;
	while (element_list)
	{
		next = element_list->next;
		result = create_command(&cmd, element_list->data); // set cmd
		if (result != NO_ERROR)
			return (error_create_command_list(cmd_list, element_list));
		
		result = push_command(cmd_list, &cmd); // aup cmd to tail of cmd_list // malloc new node
		if (result != NO_ERROR)
		{
			free_simple_command(&cmd);
			return (error_create_command_list(cmd_list, element_list));
		}
		free(element_list);
		element_list = next;
	}
	return (NO_ERROR);
}
