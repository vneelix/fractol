#include "fractol.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *tmp;
	unsigned char *tmp2;

	tmp = (unsigned char*)s1;
	tmp2 = (unsigned char*)s2;
	while (*tmp != '\0')
	{
		if (*tmp != *tmp2)
			return (*tmp - *tmp2);
		tmp++;
		tmp2++;
	}
	return (*tmp - *tmp2);
}
