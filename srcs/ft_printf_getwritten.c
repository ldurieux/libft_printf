/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_getwritten.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:47:13 by ldurieux          #+#    #+#             */
/*   Updated: 2022/08/22 13:47:14 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

typedef union u_cast
{
	t_int64	lld;
	t_int32	d;
	t_int16	hd;
	t_int8	hhd;
}	t_cast;

void	ft_printf_getwritten(int written, t_printf_conversion conv,
						t_printf_arg arg)
{
	t_cast	cast;

	cast.d = written;
	if (conv.length_mod & L_Int_Min)
		*((t_int8 *)arg.p) = cast.hhd;
	else if (conv.length_mod & L_Int_Small)
		*((t_int16 *)arg.p) = cast.hd;
	else if (conv.length_mod & L_Int_Long
		|| conv.length_mod & L_Int_LongLong
		|| conv.length_mod & L_Int_Max
		|| conv.length_mod & L_Int_Size
		|| conv.length_mod & L_Ptrdiff)
		*((t_int64 *)arg.p) = cast.lld;
	else
		*((t_int32 *)arg.p) = cast.d;
}
