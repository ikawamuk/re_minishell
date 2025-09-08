/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 02:25:41 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 17:40:25 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parse.h"

int	parse(t_element **element_list, char *str);
int expand(t_element_list *element_list, char **envp);
static void	*free_element_list(t_element_list *list);
static int create_command_list(t_command_list **cmd_list, t_element_list *element_list);

/*
	create command list from str.
	return 0 if succeed, else non-zero.
*/

int	parse_command(t_command_list **cmd_list, char *str, char **envp)
{
	int				result;
	t_element_list	*element_list;

	element_list = NULL;
	result = parse(&element_list, str); // yyparse // get_command_list_element
	if (result == ERROR)
		return (free_element_list(element_list), ERROR);
	gather_heredoc(element_list); // heredocが必要かどうかはココで判定する
	result = expand(element_list, envp); // コマンド引数の環境変数展開,  コマンド引数の単語分割、空文字削除, リダイレクト部の展開
	if (result != NO_ERROR)
		return (free_element_list(element_list), ERROR);
	result = create_command_list(cmd_list, element_list); // なかで適切にelenentlistをcleanする
	if (result != NO_ERROR)
		return (free_element_list(element_list), ERROR);
	return (result);
}


static void free_command(t_simple_cmd cmd);
static void *free_command_list(t_command_list *cmd);
int push_command(t_command_list **cmd_list, t_simple_cmd *cmd);
int error_create_command_list(t_command_list **cmd_list, t_element_list *element_list);

static int create_command_list(t_command_list **cmd_list, t_element_list *element_list) // cmd_list の所有権あり
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
		free_element(element_list->data);
		free(element_list);
		element_list = next;
	}
	return (NO_ERROR);
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

int create_redirect_list(t_simple_cmd *cmd, t_redir_word_list *rword_list)
{
	t_redir_word_list	*next_word;
	t_redir_list		*next_node;

	if (!rword_list)
		return (NULL);
	while (rword_list)
	{
		next_node = cmd->redir->next;
		next_word = rword_list->next;
		cmd->redir->redir.file_name = strdup(rword_list->data.rword.value);
		if (!cmd->redir->redir.file_name)
			return (error_create_redirect_list(cmd, rword_list));
		cmd->redir = next_node;
		free(rword_list->data.rword.value);
		free(rword_list);
		rword_list = next_word;
	}
	return (NO_ERROR);
}

int error_create_redirect_list(t_simple_cmd *cmd, t_redir_word_list *rword_list)
{
	cmd->redir = free_redirect_list(cmd->redir);
	rword_list = free_rword_list(rword_list);
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

static void	*free_rword_list(t_redir_word_list *list)
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

int	error_create_argv(t_simple_cmd *cmd, t_word_list *list)
{
	list = free_word_list(list);
	cmd->argv = free_2darr(cmd->argv);
	return (ERROR);
}

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

int error_create_command(t_simple_cmd *cmd, t_element element)
{
	return (ERROR);
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
	cmd->redir = NULL;
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


static void free_simple_command(t_simple_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->argv = free_2darr((void *)cmd->argv);
	cmd->redir = free_redirect_list(cmd->redir);
}

static void *free_redirect_list(t_redir_list *list)
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

static void *free_2darr(void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static void *free_command_list(t_command_list *cmd)
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

static void free_element(t_element element);

static void	*free_element_list(t_element_list *list)
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

static void free_element(t_element element)
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
