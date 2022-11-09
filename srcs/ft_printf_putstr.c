#include "ft_printf_internal.h"

int	ft_printf_putstr(int fd, t_printf_conversion conv, char *str)
{
	size_t	size;
	size_t	i;
	size_t	str_len;

	str_len = ft_strlen(str);
	if (conv.precision != -1)
		if (conv.precision < (int)str_len)
			str_len = (size_t)conv.precision;
	size = 0;
	if (conv.width > 0)
		size = (size_t)conv.width;
	if (size <= str_len)
		size = 0;
	else
		size -= str_len;
	i = (size_t)-1;
	while (++i < size && !(conv.flags & F_Left_Adjusted))
		write(fd, " ", 1);
	write(fd, str, str_len);
	while (++i - 1 < size && conv.flags & F_Left_Adjusted)
		write(fd, " ", 1);
	return ((int)(size + str_len));
}
