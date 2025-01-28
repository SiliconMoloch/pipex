/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:58 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/21 17:24:43 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static int	sign_print(int negative, t_flags flags)

{
	if (negative)
		return ((int)write(1, "-", 1));
	else if (flags.plus)
		return ((int)write(1, "+", 1));
	else if (flags.space)
		return ((int)write(1, " ", 1));
	return (0);
}

static int	calculate_total_length(int digits, int negative, t_flags flags)

{
	int	total_length;

	total_length = digits;
	if (negative || flags.plus || flags.space)
		total_length += 1;
	if (flags.precision > digits)
		total_length += (flags.precision - digits);
	return (total_length);
}

static int	int_min_handler(t_flags flags)

{
	int	x;
	int	total_length;
	int	padding;

	x = 0;
	total_length = calculate_total_length(10, 1, flags);
	padding = flags.width - total_length;
	if (!flags.minus && (!flags.zero || flags.precision != -1))
		x += padding_print(padding, flags);
	x += sign_print(1, flags);
	if (flags.zero && flags.precision == -1)
		x += padding_print(padding, flags);
	else
		x += precision_print(flags.precision, 10);
	x += (int)write(1, "2147483648", 10);
	if (flags.minus)
		x += padding_print(padding, flags);
	return (x);
}

int	handle_d_and_i(int n, t_flags flags)

{
	int	x;
	int	digits;
	int	negative;
	int	total_length;

	x = 0;
	negative = n < 0;
	if (n == INT_MIN)
		return (int_min_handler(flags));
	n = ft_abs(n);
	digits = digits_count(n, 10);
	if (n == 0 && flags.precision == 0)
		digits = 0;
	total_length = calculate_total_length(digits, negative, flags);
	if (!flags.minus && (!flags.zero || flags.precision >= 0))
		x += padding_print((flags.width - total_length), flags);
	x += sign_print(negative, flags);
	if (!flags.minus && flags.zero && flags.precision < 0)
		x += padding_print((flags.width - total_length), flags);
	x += precision_print(flags.precision, digits);
	if (digits > 0)
		x += ft_putnbr_base(n, RADIX_X);
	if (flags.minus && (!flags.zero || flags.precision >= 0))
		x += padding_print((flags.width - total_length), flags);
	return (x);
}
