/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:07:03 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/21 17:12:34 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static const char	*parse_flags2(const char *format, t_flags *flags)

{
	if (*format >= '0' && *format <= '9')
		flags->width = 0;
	while (*format >= '0' && *format <= '9')
		flags->width = flags->width * 10 + (*format++ - '0');
	if (*format == '.')
	{
		format++;
		flags->precision = 0;
		while (*format >= '0' && *format <= '9')
			flags->precision = flags->precision * 10 + (*format++ - '0');
	}
	if (specifier(*format))
		flags->specifier = *format;
	return (format);
}

const char	*parse_flags(const char *f, t_flags *flags)

{
	while (*f == '-' || *f == '0' || *f == '#' || *f == ' ' || *f == '+')
	{
		if (*f == '-')
		{
			flags->minus = 1;
			flags->zero = 0;
		}
		if (*f == '0' && !flags->minus)
			flags->zero = 1;
		if (*f == '#')
			flags->hash = 1;
		if (*f == ' ')
		{
			if (!flags->plus)
				flags->space = 1;
		}
		if (*f == '+')
		{
			flags->plus = 1;
			flags->space = 0;
		}
		f++;
	}
	f = parse_flags2(f, flags);
	return (f);
}

void	initialize_flags(t_flags *flags)

{
	flags->minus = 0;
	flags->zero = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->specifier = '\0';
}
