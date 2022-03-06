/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:38:48 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 17:36:26 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fifteen_puzzle.h"

extern t_envs	e;

/**
 * @brief		set size (grid/cell/stat/back)
** @param		argc	argument count
** @param		argv	argument contents
 */
static void		set_size(int argc, char **argv)
{
	// [ grid size ]
	int grid_height = 0;
	int grid_width = 0;
	if (2 <= argc)
	{
		grid_height = atoi(argv[1]);
		grid_width = atoi(argv[2]);
	}
	// height
	if (GRID_SIZE_MIN <= grid_height && grid_height <= GRID_SIZE_MAX)
		e.grid_size.height = grid_height;
	else
		e.grid_size.height = GRID_HEIGHT;
	// width
	if (GRID_SIZE_MIN <= grid_width && grid_width <= GRID_SIZE_MAX)
		e.grid_size.width = grid_width;
	else
		e.grid_size.width = GRID_WIDTH;

	// [ cell_size ]
	e.cell_size = e.grid_size.height * e.grid_size.width;

	// [ stat_size ]
	e.stat_size.height = STAT_HEIGHT;
	e.stat_size.width = e.grid_size.width * 2 - 1;

	// [ back size ]
	// height
	e.back_size.height = e.grid_size.height * 2 + 1;
	e.back_size.height += e.stat_size.height + 1;
	// width
	e.back_size.width = e.grid_size.width * 2 + 1;
}

/**
 * @brief		set coord (back/grid/stat)
 */
static void		set_coord(void)
{
	// [ set back coord ]
	e.back_coord.y = 0;
	e.back_coord.x = 0;
	
	// [ grid coord ]
	e.grid_coord.y = 1;
	e.grid_coord.x = 1;

	// [ stat_coord ]
	e.stat_coord.y = e.grid_coord.y + e.grid_size.height * 2;
	e.stat_coord.x = e.grid_coord.x;
}

/**
 * @brief		initialize environment variables
** @param		argc	argument count
** @param		argv	argument contents
 */
void			init_envs(int argc, char **argv)
{
	// [ set size ]
	set_size(argc, argv);
	// [ set coord ]
	set_coord();
}