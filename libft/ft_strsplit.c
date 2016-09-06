/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 09:15:12 by lguarda           #+#    #+#             */
/*   Updated: 2015/02/13 23:30:48 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	ft_get_splits_number(char const *s, char c)
{
	size_t i;
	size_t n;

	n = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c) && (i == 0 || s[i - 1] == c))
			n++;
		i++;
	}
	return (n);
}

static size_t	ft_get_len(char const *s, char c, size_t start)
{
	size_t len;

	len = 0;
	while (s[start + len] && s[start + len] != c)
		len++;
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	start;
	size_t	len;
	size_t	splits;
	size_t	i;
	char	**out;

	splits = ft_get_splits_number(s, c);
	out = (char**)malloc(sizeof(char*) * (splits + 1));
	out[splits] = 0;
	i = 0;
	start = 0;
	while (i < splits && s[start])
	{
		while (s[start] == c && s[start])
			start++;
		len = ft_get_len(s, c, start);
		out[i] = ft_strsub(s, (unsigned int)start, len);
		start += len;
		i++;
	}
	return (out);
}
