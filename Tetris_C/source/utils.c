/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 05:38:47 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/04 22:06:33 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_vars	v;

int				is_filled_cell(t_cell cell)
{
	// [ cell is filled ? ]
	if (cell.c == '\0')
		return -1;
	return 0;
}

static int		is_cell_in_field(int y, int x)
{
	// [ cell is in field ? ]
	if ((0 <= y && y < e.field_size.height) && 
		(0 <= x && x < e.field_size.width))
		return 0;
	else
		return -1;
}

int				check_range(t_cell cell, int y, int x)
{
	if (cell.c == '\0')
		return -1;
	return is_cell_in_field(y, x);
}

int				check_cell(t_cell cell_self, int y, int x)
{
	if (check_range(cell_self, y, x) ||
		v.field[calc_field_index(y, x)].c != '\0')
		return -1;

	return 0;
}
