/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:24:43 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/09 19:40:10 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <string.h>
#include <stdio.h>

t_parse_info init_info(char *str);
int	get_element(t_element *element, t_parse_info *info);
static void 	*free_element(t_element element);
t_token_type	lex(char **token_value, const char *str, size_t *ip);
int	push_element(t_element_list **list, t_element node);

int	parse(t_element_list **element_list, char *str)
{
	int				result;
	t_parse_info	info;
	t_element		element;

	info = init_info(str);
	*element_list = NULL;
	while (1)
	{
		result = get_element(&element, &info);
		if (result == ERROR)
			return (free_element(element), ERROR);
		// printf("top word of element: %s\n", element.word_list->data.value);
		result = push_element(element_list, element);
		// printf("top word of top of list: %s\n", (*element_list)->data.word_list->data.value);
		if (result == ERROR)
        	return (free_element(element), ERROR);
		if (info.prev_token == T_NULL)
			break ;
	}
	return (NO_ERROR);
}

static void 	*free_element(t_element element)
{
	t_word_list			*tmp_w;
	t_redir_word_list	*tmp_r;

	while (element.word_list)
	{
		free(element.word_list->data.value);
		tmp_w = element.word_list;
		element.word_list = element.word_list->next;
		free(tmp_w);
	}
	while (element.rword_list)
	{
		free(element.rword_list->data.rword.value);
		tmp_r = element.rword_list;
		element.rword_list = element.rword_list->next;
		free(tmp_r);
	}
	return (NULL);
}

int get_node(t_element_node *node, t_parse_info *info);
int	push_word_list(t_word_list **list, t_word node);
int	push_rword_list(t_redir_word_list **list, t_redir_word node);
void	*free_element_node(t_element_node node);

int	get_element(t_element *element, t_parse_info *info)
{
	int				result;
	t_element_node	node;

	memset(element, 0, sizeof(*element)); // ここ
	while (1)
	{
		result = get_node(&node, info);
		// printf("node: %s\n", node.data.word.value);
		if (result == ERROR)
			return (free_element_node(node), ERROR);
		if (result == CMD_FINISH)
			break ;
		
		if (node.type == WORD_NODE)
			result = push_word_list(&element->word_list, node.data.word);
		else if (node.type == RWORD_NODE)
			result = push_rword_list(&element->rword_list, node.data.rword);
		if (result == ERROR)
			return (free_element_node(node), ERROR);
	}
	free_element_node(node);
	return (NO_ERROR);
}

void	*free_element_node(t_element_node node)
{
	if (node.type == WORD_NODE)
		free(node.data.word.value);
	else
		free(node.data.rword.rword.value);
	return (NULL);
}

int	get_valid_token(t_token *valid_token, t_parse_info *info);
void	*free_token(t_token token);
void	convert_token_to_node(t_element_node *node, t_token token);

int get_node(t_element_node *node, t_parse_info *info)
{
	int		result;
	t_token	token;

	memset(node, 0, sizeof(*node)); //こう？
	result = get_valid_token(&token, info);
	// printf("valid token: %s\n", token.word.value);
	if (result == ERROR)
		return (free_token(token), ERROR);
	if (result == CMD_FINISH)
		return (CMD_FINISH);
	convert_token_to_node(node, token);
	return (NO_ERROR);
}

#include <stdbool.h>
bool	is_command_terminator(t_token_type type);
bool	is_redirect_operator(t_token_type type);
bool	is_command_connector(t_token_type type);
int		vaidated_lex(t_token *token, t_parse_info *info);

int	get_valid_token(t_token *valid_token, t_parse_info *info)
{
	int		result;
	t_token	tmp_token;

	if (!valid_token)
		return (ERROR);
	memset(valid_token, 0, sizeof(*valid_token));
	result = vaidated_lex(&tmp_token, info);
	if (result == ERROR)
		return (free_token(tmp_token), ERROR);
	if (is_command_terminator(tmp_token.type))
		return (CMD_FINISH);
	if (tmp_token.type == T_WORD)
	{
		*valid_token = tmp_token;
		memset(&tmp_token, 0, sizeof(tmp_token)); // なくてもいい
	}
	else if (is_redirect_operator(tmp_token.type))
	{
		valid_token->type = tmp_token.type;
		memset(&tmp_token, 0, sizeof(tmp_token));
		result = vaidated_lex(&tmp_token, info);
		if (result == ERROR || tmp_token.type != T_WORD) 
			return (free_token(tmp_token), ERROR);
		valid_token->word = tmp_token.word;
		memset(&tmp_token, 0, sizeof(tmp_token)); // なくてもいい
	}
	return (NO_ERROR);
}

void	*free_token(t_token token)
{
	free(token.word.value);
	return (NULL);
}

bool is_valid_token_sequence(t_token_type token_type, t_parse_info *info);

int	vaidated_lex(t_token *token, t_parse_info *info)
{
	if (!token)
		return (ERROR);
	memset(token, 0, sizeof(*token));
	token->type = lex(&token->word.value, info->str, &info->str_i);
	if (!is_valid_token_sequence(token->type, info))
		return (ERROR);
	info->prev_token = token->type;
	
	return (NO_ERROR);
}

bool is_valid_token_sequence(t_token_type token_type, t_parse_info *info)
{
	if (T_ERROR == token_type)
		return (false);
	if (is_command_terminator(token_type))
	{
		if (info->prev_token != T_WORD)
			return (false);
		info->prev_token = token_type;
	}
	else if (is_redirect_operator(token_type))
	{
		if (is_redirect_operator(info->prev_token))
			return (false);
		info->prev_token = token_type;
	}
	return (true);
}

void convert_token_to_node(t_element_node *node, t_token token)
{
	if (token.type == T_WORD)
	{
		node->type = WORD_NODE;
		node->data.word = token.word;
		return ;
	}
	node->type = RWORD_NODE;
	node->data.rword.type = token.type;
	node->data.rword.rword = token.word;
	return ;
}


bool	is_redirect_operator(t_token_type type)
{
	if (type == T_GREATER)
		return (true);
	if (type == T_GREATER_GREATER)
		return (true);
	if (type == T_LESS)
		return (true);
	if (type == T_LESS_LESS)
		return (true);
	return (false);
}

bool	is_command_connector(t_token_type type)
{
	if (type == T_BAR)
		return (true);
	if (type == T_BAR_BAR)
		return (true);
	if (type == T_AND_AND)
		return (true);
	return (false);
}

bool	is_command_terminator(t_token_type type)
{
	return (is_command_connector(type) || type == T_NULL);
}

int	push_word_list(t_word_list **list, t_word node)
{
	t_word_list	*tail;
	t_word_list	*new;

	if (!list)
		return (ERROR);
	new = malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->next = NULL;
	new->data = node;
	if (!*list)
	{
		*list = new;
		return (NO_ERROR);
	}
	tail = *list;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	return (NO_ERROR);
}

int	push_rword_list(t_redir_word_list **list, t_redir_word node)
{
	t_redir_word_list	*tail;
	t_redir_word_list	*new;

	if (!list)
		return (ERROR);
	new = malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->next = NULL;
	new->data = node;
	if (!*list)
	{
		*list = new;
		return (NO_ERROR);
	}
	tail = *list;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	return (NO_ERROR);
}

int	push_element(t_element_list **list, t_element node)
{
	t_element_list	*tail;
	t_element_list	*new;

	if (!list)
		return (ERROR);
	new = malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->next = NULL;
	new->data = node;
	if (!*list)
	{
		*list = new;
		return (NO_ERROR);
	}
	tail = *list;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	return (NO_ERROR);
}

t_parse_info init_info(char *str)
{
	t_parse_info	info;

	info.str = str;
	info.str_i = 0;
	info.prev_token = T_NULL;
	return (info);
}