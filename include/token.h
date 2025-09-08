/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:22:16 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 18:28:01 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "config.h"

typedef struct s_element			t_element;
typedef struct s_element_list		t_element_list;
typedef struct s_state_list			t_state_list;
typedef struct s_token_list			t_token_list;
typedef struct s_token				t_token;
typedef struct s_word				t_word;
typedef struct s_word_list			t_word_list;
typedef struct s_redir_word_list	t_redir_word_list;

struct s_word
{
	int 	flag;
	char	*value;
};

struct s_token
{
	t_token_type	type;
	t_word			word;
};

struct s_token_list
{
	t_token			data;
	t_token_list	*next;
};

struct s_word_list
{
	t_word		data;
	t_word_list	*next;
};

typedef struct s_redir_word
{
	enum e_redir_type	type;
	t_word				rword;
}	t_redir_word;

struct s_redir_word_list
{
	t_redir_word		data;
	t_redir_word_list	*next;
};

union u_word_node
{
	t_word			word;
	t_redir_word	rword;
};

enum e_node_type
{
	WORD_NODE,
	RWORD_NODE
};

typedef struct s_element_node
{
	enum e_node_type	type;
	union u_word_node	data;
}	t_element_node;

struct s_element
{
	t_word_list			*word_list;
	t_redir_word_list	*rword_list;
};

struct s_element_list
{
	t_element		data;
	t_element_list	*next;	
};

#endif