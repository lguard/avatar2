#include "libft.h"

static float	ft_ftoi_ext(const char **str)
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

float			ft_ftoi(const char *str)
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
