/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 17:11:50 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/10 12:43:26 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char				*str;
	unsigned int		i;

	str = ft_strnew(len + 1);
	i = start;
	while (i < (start + len))
	{
		str[i - start] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
