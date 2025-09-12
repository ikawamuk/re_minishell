/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:55:10 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/12 17:10:37 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "expand.h"
#include <string.h>
#include <stdbool.h>
static void	*free_word_list(t_word_list *list);
static bool	is_quote_marker(char c);
static bool	is_space(char c);
bool	is_null_node(char *string);
static bool has_next_word(char *string, size_t *start_p, size_t *index_p);
static char *substr(char const *s, unsigned int start, size_t len);
int split_word_list(t_word_list **word_list_p);
int get_split_word_list(t_word_list *word_list, t_word_list **result_list);
int split_string(char *string, t_word_list **last_p);


int split(t_element_list *element_list)
{
	while (element_list)
	{
		if (split_word_list(&element_list->data.word_list) == ERROR)
			return (ERROR);
		element_list = element_list->next;
	}
	return (NO_ERROR);
}

int split_word_list(t_word_list **word_list_p)
{
	int			rev;
	t_word_list *head;
	t_word_list *result_list;

	head = *word_list_p;
	result_list = NULL;
	rev = get_split_word_list(*word_list_p, &result_list);
	free_word_list(head);
	*word_list_p = result_list;
	return (rev);
}

int get_split_word_list(t_word_list *word_list, t_word_list **result_list)
{
	t_word_list	**result_last_p;
	t_word_list	*temp;

	result_last_p = result_list;
	while (word_list)
	{
		if (!is_null_node(word_list->data.value))
		{
			if (split_string(word_list->data.value, &temp) == ERROR)
				return (ERROR);
			*result_last_p = temp;
			while (temp && temp->next)
				temp = temp->next;
			if (temp)
				result_last_p = &temp->next;
		}
		word_list = word_list->next;
	}
	return (NO_ERROR);	
}

bool	is_null_node(char *string)
{
	while (is_space(*string))
		string++;
	return (!*string);
}

int split_string(char *string, t_word_list **last_p)
{
	char	*word;
	size_t	start = 0;
	size_t	index = 0;

	while (string[index])
	{
		if (!has_next_word(string, &start, &index))
			break ;
		word = substr(string, start, index - start);
		if (!word)
			return (ERROR);
		*last_p = malloc(sizeof(t_word_list));
		if (!*last_p)
			return (free(word), ERROR);
		(*last_p)->data.value = word;
		(*last_p)->next = NULL;
		last_p = &(*last_p)->next;
	}
	return (NO_ERROR);
}

static bool has_next_word(char *string, size_t *start_p, size_t *index_p)
{
	while (is_space(string[*index_p]))
		(*index_p)++;
	if (!string[*index_p])
		return (false);
	*start_p = *index_p;
	while (string[*index_p] && !is_space(string[*index_p]))
	{
		if (is_quote_marker(string[*index_p]))
		{
			char marker = string[*index_p];
			(*index_p)++;
			while (marker != string[*index_p])
				(*index_p)++;
			(*index_p)++;
		}
		else
			(*index_p)++;
	}
	return (true);
}

static bool	is_space(char c)
{
	return (c == ' ' || (9 <= c  && c <= 13));
}

static bool	is_quote_marker(char c)
{
	return (c == S_QUOTE_MARKER || c == D_QUOTE_MARKER);
}

static char *substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*result;

	slen = strlen(s);
	if (start > slen)
		slen = 0;
	else
		slen -= start;
	s += start;
	if (slen > len)
		slen = len;
	result = (char *)malloc((slen + 1) * sizeof(char));
	if (result)
		strncpy(result, s, slen + 1);
	return (result);
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
