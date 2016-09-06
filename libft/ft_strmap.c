/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 15:04:26 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/07 17:35:48 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	n;
	size_t	i;
	char	*s2;

	n = ft_strlen(s);
	i = 0;
	s2 = ft_strnew(n);
	while (i < n)
	{
		s2[i] = f(s[i]);
		i++;
	}
	return (s2);
}
