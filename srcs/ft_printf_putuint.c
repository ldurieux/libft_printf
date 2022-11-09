#include "ft_printf_internal.h"

static int	ft_printf_putprefix(int fd, t_printf_conversion conv)
{
	if (conv.flags & F_Alternate)
	{
		if (conv.conv & C_Octal)
			return ((int)write(fd, "0", 1));
		if (conv.conv & C_Hexa && conv.conv & C_Upper)
			return ((int)write(fd, "0X", 2));
		if (conv.conv & C_Hexa)
			return ((int)write(fd, "0x", 2));
	}
	return (0);
}

int	ft_printf_putuint(int fd, t_printf_conversion conv, t_uint64 val)
{
	char	*number;
	size_t	number_len;
	size_t	res_len;
	int		i;
	char	a_chr;

	a_chr = (char)(' ' + ((conv.flags & F_Zero_Padded) != 0) * ('0' - ' '));
	res_len = 0;
	number = ft_printf_ulltoa(val, conv, ft_printf_base(conv), &number_len);
	conv.precision = (int)ft_max(conv.precision, (t_int64)number_len);
	conv.width = (int)ft_max(conv.precision, conv.width);
	conv.width -= ft_printf_setalter(val, number, (int)number_len, &conv);
	if (!(conv.flags & F_Left_Adjusted))
		res_len += ft_printf_putalign(fd, conv.width - conv.precision, a_chr);
	res_len += ft_printf_putprefix(fd, conv);
	i = conv.precision;
	while (i-- > (int)number_len)
		res_len += write(fd, "0", 1);
	res_len += write(fd, number, number_len);
	if (conv.flags & F_Left_Adjusted)
		res_len += ft_printf_putalign(fd, conv.width - conv.precision, a_chr);
	free(number);
	return ((int)(res_len));
}
