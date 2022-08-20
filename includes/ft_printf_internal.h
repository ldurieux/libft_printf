/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:07:55 by ldurieux          #+#    #+#             */
/*   Updated: 2022/08/20 14:07:58 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <stdarg.h>
# include "libft.h"

enum e_flags
{
	F_Alternate			= 0x1,
	F_Zero_Padded		= 0x2,
	F_Left_Adjusted		= 0x4,
	F_Space_Prefixed	= 0x8,
	F_Force_Sign		= 0x10,
};

enum e_length_modifier
{
	L_Int_Min		= 0x1,
	L_Int_Small		= 0x2,
	L_Int_Long		= 0x4,
	L_Int_LongLong	= 0x8,
	L_Int_Max		= 0x10,
	L_Int_Size		= 0x20,
	L_Double_Long	= 0x40,
	L_Ptr_Diff		= 0x80,
};

enum e_conversion
{
	C_Int			= 0x1,
	C_Double		= 0x2,
	C_Char			= 0x4,
	C_String		= 0x8,
	C_Pointer		= 0x10,
	C_Get_Written	= 0x20,
	C_Percent		= 0x40,
	C_Decimal		= 0x80,
	C_Octal			= 0x100,
	C_Hexa			= 0x200,
	C_Scientific	= 0x400,
	C_Smallest		= 0x800,
	C_Upper			= 0x1000,
	C_Unsigned		= 0x2000,
};

typedef struct s_printf_conversion
{
	int			width;
	int			precision;
	t_uint8		flags;
	t_uint8		length_mod;
	t_uint16	conv;
}	t_printf_conversion;

t_printf_conversion	ft_printf_parse_conversion(char **format, va_list args);

#endif