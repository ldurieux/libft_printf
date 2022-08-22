#include "ft_printf_internal.h"

char	*ft_printf_base(t_printf_conversion conv)
{
	if (conv.conv & C_Decimal)
		return ("0123456789");
	if (conv.conv & C_Octal)
		return ("01234567");
	if (conv.conv & C_Hexa && !(conv.conv & C_Upper))
		return ("0123456789abcdef");
	if (conv.conv & C_Hexa)
		return ("0123456789ABCDEF");
	return (NULL);
}

int	ft_printf_setalter(t_uint64 val, const char *number,
						int number_len, t_printf_conversion *conv)
{
	if ((conv->conv & C_Octal && (number[0] == '0'
				|| conv->precision < number_len))
		|| (conv->conv & C_Hexa && (val == 0)))
		conv->flags &= ~F_Alternate;
	if (conv->flags & F_Alternate)
	{
		if (conv->conv & C_Octal)
			return (1);
		if (conv->conv & C_Hexa)
			return (2);
	}
	return (0);
}
