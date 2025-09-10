/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 06:50:55 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/10 21:42:23 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "command.h"

int expand(t_element_list *element_list, char **envp)
{
	int result;

	quote(element_list); // クオートマーカーセット
	// word listの展開
	// word listの単語分割、空文字列削除
		// リダイレクトの展開は実行部でやろう。
		// redirect word listの展開
		// redirect word listで単語分割、空文字列が発生した場合はambiguas redirectでエラー
	// ワイルドカードの展開（グロブ展開）
	if (dequote(element_list) == ERROR)
		return (ERROR); // クオート除去
	return (NO_ERROR);
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
