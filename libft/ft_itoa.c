/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:30 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/07 12:07:58 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char		*exept(void)
{
	char	*str;

	str = ft_strnew(12);
	ft_strcpy(str, "-2147483648");
	return (str);
}

char			*ft_itoa(int n)
{
	int		i;
	int		z;
	char	*str;

	i = 1;
	z = n;
	if (n == -2147483648)
		return (exept());
	if (n < 0 && i++)
		n = (-n);
	while (!((z >= -9) && (z <= 9)) && i++)
		z /= 10;
	str = ft_strnew(i + 1);
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		if (z < 0 && i == 0)
			str[i] = '-';
		else
			str[i] = ((n % 10) + '0');
		n /= 10;
		i--;
	}
	return (str);
}
