/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:42:54 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/07 17:36:35 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	n;
	size_t	i;
	char	*s2;

	n = ft_strlen(s);
	i = 0;
	s2 = ft_strnew(n);
	while (i < n)
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	return (s2);
}
