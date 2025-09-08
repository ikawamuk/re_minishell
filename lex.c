/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:43:54 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 15:18:51 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include <stdbool.h>
#define UNCLOSED_QUOTE	-1

char			*ft_strndup(const char *s, size_t n);
bool			is_space(char c);
bool			is_metachar(char c);
bool			is_quote(char c);
int				skip_quoted_part(char quote, char *str, size_t *ip);
t_token_type	get_special_token(char **token_value, char *str, size_t *ip);
int				get_word(char **token_value, char *str, size_t *ip);

t_token_type	lex(char **token_value, char *str, size_t *ip)
{
	*token_value = NULL;
	while (str[*ip] && is_space(str[*ip]))
	{
		if ((*ip))
			continue;	
		if (is_metachar(str[*ip]))
			return(get_special_token(token_value, str, ip));
		return (get_word(token_value, str, ip));
	}
	return (T_NULL);
}

// static bool	is_redirect(t_token_type type)
// {
// 	return (T_GREATER <= type && type <= T_LESS_LESS);
// }

t_token_type	detect_special_token_type(char *head);

t_token_type	get_special_token(char **token_value, char *str, size_t *ip)
{
	t_token_type	type;
	char			*head;

	head = str + *ip;
	type = detect_special_token_type(head);
	if (*head == *(head + 1))
		*ip += 2;
	else
		(*ip)++;
	// if (is_redirect(type))
	// {
	// 	while (str[*ip] && is_space(str[*ip]))
	// 	(*ip)++;
	// 	if (!str[*ip])
	// 		return (T_NULL);
	// 	if (is_metachar(str[*ip]))
	// 		return (T_ERROR);
	// 	if (get_word(token_value, str, ip) != NO_ERROR)
	// 		return (T_ERROR);
	// }
	*token_value = NULL;
	return (type);
}

t_token_type	detect_special_token_type(char *head)
{
	if (*head == '<')
	{
		if (*head == *(head + 1))
			return (T_LESS_LESS);
		return (T_LESS);
	}
	if (*head == '>')
	{
		if (*head == *(head + 1))
			return (T_GREATER_GREATER);
		return (T_GREATER);
	}
	if (*head == '|')
	{
		if (*head == *(head + 1))
			return (T_BAR_BAR);
		return (T_BAR);
	}
	if (*head == '&' && *head == *(head + 1))
		return (T_AND_AND);
	return (T_ERROR);
}

int	get_word(char **token_value, char *str, size_t *ip)
{
	char	*head;

	*token_value = NULL;
	if (!str[*ip])
		return (ERROR);
	head = str + *ip;	
	while (str[*ip] && !is_space(str[*ip]) && !is_metachar(str[*ip]))
	{
		if (is_quote(str[*ip]))
		{
			if (skip_quoted_part(str[*ip], str, ip) == UNCLOSED_QUOTE)
				return (ERROR);
		}
		else
			(*ip)++;
	}
	*token_value = ft_strndup(head, &str[*ip] - head);
	return (NO_ERROR);	
}

int	skip_quoted_part(char quote, char *str, size_t *ip)
{
	(*ip)++;
	while (str[*ip] && str[*ip] != quote)
		(*ip)++;
	if (!str[*ip])
		return (UNCLOSED_QUOTE);
	(*ip)++;
	return (NO_ERROR);
}

bool	is_metachar(char c)
{
	return (c == '<'|| c == '>' || c == '|' || c == '&');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	is_space(char c)
{
	return (c == ' ' || (9 <= c  && c <= 13));
}

# include <stdint.h>
static char	*ft_strncpy(char *dest, const char *src, size_t n);

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
		p[i++] = '\0';
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;

	result = ft_calloc(n + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	return (ft_strncpy(result, s, n));
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

