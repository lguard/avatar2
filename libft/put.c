/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 03:04:24 by lguarda           #+#    #+#             */
/*   Updated: 2015/02/19 07:02:18 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		ft_putsn(char *str, int *fd)
{
	int		len;

	len = 0;
	while (str[len] && str[len] != '%')
		len++;
	write(*fd, str, len);
	return (len);
}

static void		print_s(va_list ap, char **str, int *fd)
{
	if (**str == 'c')
		return (ft_putchar_fd(va_arg(ap, int), *fd));
	else if (**str == 's')
		return (ft_putstr_fd(va_arg(ap, char*), *fd));
	else if (**str == 'd' || **str == 'i')
		return (ft_putnbr_fd(va_arg(ap, int), *fd));
	else if (**str == '%')
		return (ft_putchar_fd('%', *fd));
	else if (**str == 'E')
		*fd = 2;
	else if (**str == 'e')
		*fd = 1;
}

static void		print_arg(va_list ap, char **str, int *fd)
{
	*str += 1;
	print_s(ap, str, fd);
}

void			put(char *str, ...)
{
	va_list	ap;
	int		tmp;
	int		fd;

	va_start(ap, str);
	fd = 1;
	while (*str)
	{
		tmp = ft_putsn(str, &fd);
		str += tmp;
		if (*str == '%')
			print_arg(ap, &str, &fd);
		str += (*str) ? 1 : 0;
	}
	va_end(ap);
}
