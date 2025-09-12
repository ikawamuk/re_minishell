/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:36:09 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/12 19:44:46 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "expand.h"
#include <stdio.h>
#include <stdbool.h>


void quote(t_element_list *element_list);
void quote_element_list(t_element_list *element_list);
void quote_element(t_element *element);
// void quote_rword_list(t_redir_word_list *rword_list);
void quote_word_list(t_word_list *word_list);
void quote_word(t_word *word);
void quote_string(char *str);
void mark_quote(char **str_p);
void skip_quote(char **str_p);
static bool is_quote(char c);

void quote(t_element_list *element_list)
{
	quote_element_list(element_list);
}

void quote_element_list(t_element_list *element_list)
{
	while (element_list)
	{
		quote_element(&element_list->data);
		element_list = element_list->next;
	}
	return ;
}

void quote_element(t_element *element)
{
	quote_word_list(element->word_list);
	// quote_rword_list(element->rword_list);
	return ;
}

// void quote_rword_list(t_redir_word_list *rword_list)
// {
// 	while (rword_list)
// 	{
// 		quote_word(&rword_list->data.rword);
// 		rword_list = rword_list->next;
// 	}
// 	return ;
// }

void quote_word_list(t_word_list *word_list)
{
	while (word_list)
	{
		quote_word(&word_list->data);
		word_list = word_list->next;
	}
	return ;
}

void quote_word(t_word *word)
{
	quote_string(word->value);
	return ;
}


void quote_string(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			mark_quote(&str);
		else
			str++;
	}
	return ;
}

void mark_quote(char **str_p)
{
	char quote;

	quote = **str_p;
	if (quote == '\'')
		**str_p = S_QUOTE_MARKER;
	else if (quote == '"')
		**str_p = D_QUOTE_MARKER;
	(*str_p)++;
	while (quote != **str_p)
		(*str_p)++;
	if (quote == '\'')
		**str_p = S_QUOTE_MARKER;
	else if (quote == '"')
		**str_p = D_QUOTE_MARKER;	
	(*str_p)++;
	return ;
}

static bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}



int dequote(t_element_list *element_list);
int dequote_element_list(t_element_list *element_list);
int dequote_element(t_element *element);
// int dequote_rword_list(t_redir_word_list *rword_list);
int dequote_word_list(t_word_list *word_list);
int dequote_word(t_word *word);
int dequote_string(char **str_p);
int append_char(char **str_p, char c);
static bool	is_quote_marker(char c);

static bool	is_quote_marker(char c)
{
	return (c == S_QUOTE_MARKER || c == D_QUOTE_MARKER);
}

int dequote(t_element_list *element_list)
{
	return (dequote_element_list(element_list) != ERROR);
}
int dequote_element_list(t_element_list *element_list)
{
	while (element_list)
	{
		if (dequote_element(&element_list->data) == ERROR)
			return (ERROR);
		element_list = element_list->next;
	}
	return (NO_ERROR);
}

int dequote_element(t_element *element)
{
	if (dequote_word_list(element->word_list) != NO_ERROR)
		return (ERROR);
	// if (dequote_rword_list(element->rword_list) != NO_ERROR)
	// 	return (ERROR);
	return (ERROR);
}

// int dequote_rword_list(t_redir_word_list *rword_list)
// {
// 	while (rword_list)
// 	{
// 		if (dequote_word(&rword_list->data.rword) == ERROR)
// 			return (ERROR);
// 		rword_list = rword_list->next;
// 	}
// 	return (NO_ERROR);
// }

int dequote_word_list(t_word_list *word_list)
{
	while (word_list)
	{
		if (dequote_word(&word_list->data) == ERROR)
			return (ERROR);
		word_list = word_list->next;
	}
	return (NO_ERROR);
}

int dequote_word(t_word *word)
{
	return (dequote_string(&word->value));
}
#include <string.h>
int dequote_string(char **str_p)
{
	int rev;
	char *str;
	char *new_str;

	str = *str_p;
	new_str = strdup("");
	while (*str)
	{
		if (!is_quote_marker(*str))
		{
			rev = append_char(&new_str, *str);
			if (rev == ERROR)
				return (ERROR);
		}	
		str++;
	}
	*str_p = new_str;
	return (NO_ERROR);
}

#include <stdlib.h>
#include <string.h>
int append_char(char **str_p, char c)
{
	char	*new_str;
	size_t	len;

	len = strlen((*str_p)) + 2;
	new_str = calloc(sizeof(char), len);
	if (!new_str)
		return (ERROR);
	strncpy(new_str, *str_p, len);
	new_str[len - 2] = c;
	free(*str_p);
	*str_p = new_str;
	return (NO_ERROR);
}
