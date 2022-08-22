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

static int	ft_printf_putuint(int fd, t_printf_conversion conv, t_uint64 val)
{
	char	*number;
	t_size	number_len;
	t_size	res_len;
	int		i;

	res_len = 0;
	number = ft_printf_ulltoa(val, conv, ft_printf_base(conv), &number_len);
	conv.precision = (int)ft_max(conv.precision, (t_int64)number_len);
	conv.width = (int)ft_max(conv.precision, conv.width);
	conv.width -= ft_printf_setalter(val, number, (int)number_len, &conv);
	while (conv.width-- > conv.precision && !(conv.flags & F_Left_Adjusted))
		res_len += write(fd, " ", 1);
	res_len += ft_printf_putprefix(fd, conv);
	i = conv.precision;
	while (i-- > (int)number_len)
		res_len += write(fd, "0", 1);
	res_len += write(fd, number, number_len);
	while (conv.width-- > conv.precision && conv.flags & F_Left_Adjusted)
		res_len += write(fd, " ", 1);
	return ((int)(res_len));
}

int	ft_printf_putarg(int fd, t_printf_conversion conv, t_printf_arg arg)
{
	if (conv.conv & C_Int && conv.conv & C_Unsigned)
		return (ft_printf_putuint(fd, conv, arg.u));
	if (conv.conv & C_Char)
		return ((int)write(fd, &arg.c, 1));
	if (conv.conv & C_String)
		return ((int)write(fd, arg.s, ft_strlen(arg.s)));
	if (conv.conv & C_Pointer)
	{
		conv = (t_printf_conversion)
		{0, -1, F_Alternate, 0, C_Int | C_Hexa | C_Unsigned};
		return (ft_printf_putuint(fd, conv, (t_uint64)arg.p));
	}
	if (conv.conv & C_Percent)
		return ((int)write(fd, "%", 1));
	return (-1);
}
