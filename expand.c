/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 06:50:55 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 15:12:06 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "command.h"

int expand(t_element_list *element_list, char **envp)
{
	int result;

	// word listの展開
	// word listの単語分割、空文字列削除
	// redirect word listの展開
	// redirect word listの単語分割、空文字削除
	// ワイルドカードの展開（グロブ展開）
	// クオート除去
}

int dequote(t_element_list *element_list)
{
	int result;
	t_element_list *current;

	while (current)
	{
		result = dequote_word_list(current->data.word_list);
		current = current->next;
	}
	return (NO_ERROR);
}

int dequote_word_list(t_word_list *list)
{
	int result;
	t_word_list *current;

	while (current)
	{
		result = dequote_word(&current->data);
		if (is_quoted_null(current->data))
			current->data.flag &= ~W_HASQUOTEDNULL; 
		current = current->next;
	}
}

int dequote_word(t_word *word)
{
	int result;

	
}
