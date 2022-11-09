#include "ft_printf_internal.h"

int	ft_printf_putptr(int fd, t_printf_conversion conv, t_uint64 val)
{
	char	*number;
	size_t	number_len;
	size_t	res_len;
	int		i;

	res_len = 0;
	number = ft_printf_ulltoa(val, conv, ft_printf_base(conv), &number_len);
	conv.width -= 2;
	while (conv.width-- > 0 && !(conv.flags & F_Left_Adjusted))
		res_len += (size_t)write(fd, " ", 1);
	res_len += (size_t)write(fd, "0x", 2);
	i = conv.precision;
	while (i-- > (int)number_len)
		res_len += (size_t)write(fd, "0", 1);
	res_len += (size_t)write(fd, number, number_len);
	while (conv.width-- > 0 && conv.flags & F_Left_Adjusted)
		res_len += (size_t)write(fd, " ", 1);
	free(number);
	return ((int)(res_len));
}
