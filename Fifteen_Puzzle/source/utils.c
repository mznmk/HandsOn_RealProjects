/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:12:58 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 17:42:21 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fifteen_puzzle.h"

extern t_envs	e;
extern t_vars	v;

int				conv_grid_coord(int y, int x)
{
	// [ return ]
	return e.grid_size.width * y + x;
}

/**
 * @brief		can swap cell (in range?)
 * @param		y	cell coord y
 * @param		x	cell coord x
 * @return		true (can swap): 0 / false (cannot swap): -1
 */
int				can_swap_cell(int y, int x)
{
	// [ can swap cell? ]
	if (!(0 <= y && y < e.grid_size.height))
		return -1;
	if (!(0 <= x && x < e.grid_size.width))
		return -1;
	// [ return (true) ]
	return 0;
}
