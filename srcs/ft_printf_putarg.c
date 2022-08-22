/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putarg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:26:37 by ldurieux          #+#    #+#             */
/*   Updated: 2022/08/21 13:26:38 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static char	*ft_printf_base(t_printf_conversion conv)
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

static int	ft_printf_putuint(int fd, t_printf_conversion conv, t_uint64 val)
{
	char	*number;
	t_size	number_len;
	t_size	res_len;

	number = ft_printf_lltoa(val, conv, ft_printf_base(conv), &number_len);
	conv.precision = (int)ft_max(conv.precision, (t_int64)number_len);
	conv.width = (int)ft_max(conv.precision, conv.width);
	if ((conv.conv & C_Octal && (number[0] == '0'
				|| conv.precision < (int)number_len))
		|| (conv.conv & C_Hexa && (val == 0)))
		conv.flags &= ~F_Alternate;
	conv.width -= ((conv.flags & F_Alternate) != 0)
		* (((conv.conv & C_Octal) != 0) + ((conv.conv & C_Hexa) != 0) * 2);
	res_len = conv.width;
	while (conv.width-- > conv.precision && !(conv.flags & F_Left_Adjusted))
		write(fd, " ", 1);
	if (conv.flags & F_Alternate)
	{
		if (conv.conv & C_Octal)
			write(fd, "0", 1);
		else if (conv.conv & C_Hexa && conv.conv & C_Upper)
			write(fd, "0X", 2);
		else if (conv.conv & C_Hexa)
			write(fd, "0x", 2);
		res_len += ((conv.conv & C_Octal) != 0)
			+ ((conv.conv & C_Hexa) != 0) * 2;
	}
	while (conv.precision-- > number_len)
		write(fd, "0", 1);
	write(fd, number, number_len);
	while (conv.width-- > conv.precision && conv.flags & F_Left_Adjusted)
		write(fd, " ", 1);
	return ((int)(res_len));
}

int	ft_printf_putarg(int fd, t_printf_conversion conv, t_printf_arg arg)
{
	if (conv.conv & C_Unsigned)
		return (ft_printf_putuint(fd, conv, arg.u));
	if (conv.conv & C_Percent)
		return (write(fd, "%", 1));
	return (-1);
}
