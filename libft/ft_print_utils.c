#include "libft.h"

void		ft_putnbr_base_fd_uint(int fd, unsigned int nbr, unsigned int base)
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

void		ft_putnbr_base_fd_int(int fd, int nbr, int base)
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

static void	ft_print_float(int fd, float nbr)
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
