/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 09:16:08 by lguarda           #+#    #+#             */
/*   Updated: 2015/02/13 18:03:03 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;

	while (ft_iswhite(*s))
		s++;
	i = ft_strlen(s);
	if (i)
		while (ft_iswhite(s[i - 1]))
			i--;
	str = ft_strnew(i + 1);
	if (str)
		ft_strncpy(str, s, i);
	return (str);
}
