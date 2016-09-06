/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:45:50 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/05 16:23:02 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (s[i] == c)
		return ((char *)&s[i]);
	while (s[i])
	{
		i++;
		if (s[i] == c)
			return ((char *)&s[i]);
	}
	return (NULL);
}
