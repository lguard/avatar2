/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 16:44:53 by ntibi             #+#    #+#             */
/*   Updated: 2016/08/30 17:55:49 by ntibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

#define BASE "0123456789abcdef"

static void		ft_putnbr_base_fd_uint(int fd, unsigned int nbr, unsigned int base)
{
	unsigned int tmp;
	unsigned int l;

	tmp = nbr;
	l = 1;
	while (tmp >= base)
	{
		tmp /= base;
		l *= base;
	}
	while (l)
	{
		write(fd, &BASE[nbr / l], 1);
		nbr = nbr % l;
		l /= base;
	}
}

static void		ft_putnbr_base_fd_int(int fd, int nbr, int base)
{
	unsigned int	l;
	int				tmp;

	if (nbr < 0)
	{
		nbr = -nbr;
		write(fd, "-", 1);
	}
	tmp = nbr;
	l = 1;
	while (tmp >= base)
	{
		tmp /= base;
		l *= base;
	}
	while (l)
	{
		write(fd, &BASE[nbr / l], 1);
		nbr = nbr % l;
		l /= base;
	}
}

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_print_float(int fd, float nbr)
{
	float	tmp;
	int		l;

	tmp = nbr;
	l = 1;
	while (tmp >= 10)
	{
		tmp /= 10;	
		l *= 10;
	}
	while (l)
	{
		ft_putchar_fd(((int)nbr/l)+'0', fd);
		nbr = nbr - (float)(((int)nbr/l)*(float)l);
		l /= 10;
	}
}

void	ft_putnbr_fd_float(int fd, float nbr)
{
	if (nbr < 0)
	{
		nbr = -nbr;
		write(fd, "-", 1);
	}
	ft_print_float(fd, nbr);
	write(fd, ".", 1);
	nbr -= (int)nbr;
	nbr *= 1000000;
	ft_print_float(fd, nbr);
}

size_t		ft_strlen(char *s)
{
	char *p;

	p = s;
	while (*p)
		++p;
	return (p - s);
}


static size_t	ft_putsn(char *str, int *fd)
{
	size_t len;

	len = 0;
	while (str[len] && str[len] != '%')
		++len;
	write(*fd, str, len);
	return (len);
}

size_t		ft_putstr_fd(int fd, char *s)
{
	return (write(fd, s, ft_strlen(s)));
}

static void		print_s(va_list ap, char **str, int *fd)
{
	if (**str == 's')
		ft_putstr_fd(*fd, va_arg(ap, char*));
	else if (**str == 'b')
		ft_putnbr_base_fd_uint(*fd, va_arg(ap, unsigned int), 2);
	else if (**str == 'x')
		ft_putnbr_base_fd_uint(*fd, va_arg(ap, unsigned int), 16);
	else if (**str == 'u')
		ft_putnbr_base_fd_uint(*fd, va_arg(ap, unsigned int), 10);
	else if (**str == 'd' || **str == 'i')
		ft_putnbr_base_fd_uint(*fd, va_arg(ap, unsigned int), 10);
	else if (**str == 'f')
		ft_putnbr_fd_float(*fd, va_arg(ap, double));
	else if (**str == '%')
		write(*fd, "%", 1);
	else if (**str == '2')
		*fd = 2;
	else if (**str == '1')
		*fd = 1;
}

int		ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

float			ft_ftoi_ext(const char **str)
{
	float	i;

	i = 0;
	while (ft_isdigit(**str))
	{
		i = (i * 10) + **str - '0';
		(*str) += 1;
	}
	return (i);
}

float		ft_ftoi(const char *str)
{
	float	i;
	float	j;
	int		m;

	m = 0;
	if (*str == '-')
	{
		m = 1;
		str += 1;
	}
	i = ft_ftoi_ext(&str);
	if (*str == '.')
	{
		str += 1;
		j = ft_ftoi_ext(&str);
		while (j >= 10)
		{
			j /= 10;	
		}
		i += j / 10;
	}
	if (m)
		return (-i);
	return (i);
}

void			print(char *str, ...)
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
		{
			++str;
			print_s(ap, &str, &fd);
		}
		str += (*str) ? 1 : 0;
	}
	va_end(ap);
}

int		main(void)
{
	print("%f\n", 123.321f);
	print("%f\n", ft_ftoi("123.321"));
	print("%f\n", 0.321f);
	print("%f\n", ft_ftoi("0.321"));
	print("%f\n", -0.321f);
	print("%f\n", ft_ftoi("-0.321"));
	print("%f\n", 321);
	print("%f\n", ft_ftoi("321"));
	return 0;
}
