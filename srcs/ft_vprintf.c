/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:07:38 by ldurieux          #+#    #+#             */
/*   Updated: 2022/08/20 14:07:44 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"

int	ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(STDOUT, format, ap));
}

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	(void)fd;
	(void)format;
	(void)ap;
	return (-1);
}

//NOLINTBEGIN
int	ft_vsprintf(char *str, const char *format, va_list ap)
{
	(void)str;
	(void)format;
	(void)ap;
	return (-1);
}

int	ft_vsnprintf(char *str, t_size size, const char *format, va_list ap)
{
	(void)str;
	(void)size;
	(void)format;
	(void)ap;
	return (-1);
}
//NOLINTEND
