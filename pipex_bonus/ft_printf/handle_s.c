/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:45:25 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/21 17:11:57 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static int	null_pointer_handling(t_flags flags)

{
	int	x;

	x = 0;
	if (flags.width && flags.precision >= 0 && flags.precision < 6)
	{
		while (x < flags.width)
			x += (int)write(1, " ", 1);
		return (x);
	}
	if (flags.precision >= 0 && flags.precision < 6)
		return (0);
	else
		return (handle_s("(null)", flags));
}

int	handle_s(const char *s, t_flags flags)

{
	int	x;
	int	length;

	if (!s)
		return (null_pointer_handling(flags));
	x = 0;
	length = ft_strlen(s);
	if (flags.precision >= 0 && flags.precision < length)
		length = flags.precision;
	if (flags.minus)
	{
		x += (int)write(1, s, length);
		while (x < flags.width)
			x += (int)write(1, " ", 1);
	}
	else
	{
		while (x < flags.width - length)
			x += (int)write(1, " ", 1);
		x += (int)write(1, s, length);
	}
	return (x);
}
