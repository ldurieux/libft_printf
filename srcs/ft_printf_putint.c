#include "ft_printf_internal.h"

static t_bool	ft_printf_hassign(t_int64 val, t_printf_conversion conv)
{
	if (conv.flags & F_Space_Prefixed && val >= 0)
		return (1);
	if (conv.flags & F_Force_Sign && val >= 0)
		return (1);
	if (val < 0)
		return (1);
	return (0);
}

static t_bool	ft_printf_putsign(int fd, t_int64 val, t_printf_conversion conv)
{
	if (conv.flags & F_Space_Prefixed && val >= 0)
		return (write(fd, " ", 1));
	if (conv.flags & F_Force_Sign && val >= 0)
		return (write(fd, "+", 1));
	if (val < 0)
		return (write(fd, "-", 1));
	return (0);
}

int	ft_printf_putint(int fd, t_printf_conversion conv, t_int64 val)
{
	char	*number;
	size_t	number_len;
	size_t	res_len;
	char	a_chr;
	int		has_precision;

	a_chr = (char)(' ' + ((conv.flags & F_Zero_Padded) != 0) * ('0' - ' '));
	res_len = 0;
	number = ft_printf_lltoa(val, conv, "0123456789", &number_len);
	has_precision = conv.precision != -1;
	conv.precision = (int)ft_max(conv.precision, (t_int64)number_len);
	conv.width = (int)ft_max(conv.precision, conv.width)
		- ft_printf_hassign(val, conv);
	if (!has_precision)
		res_len += ft_printf_putsign(fd, val, conv);
	if (!(conv.flags & F_Left_Adjusted))
		res_len += ft_printf_putalign(fd, conv.width - conv.precision, a_chr);
	if (has_precision)
		res_len += ft_printf_putsign(fd, val, conv);
	res_len += ft_printf_putalign(fd, conv.precision - (int)number_len, '0');
	res_len += write(fd, number, number_len);
	if (conv.flags & F_Left_Adjusted)
		res_len += ft_printf_putalign(fd, conv.width - conv.precision, a_chr);
	free(number);
	return ((int)(res_len));
}
