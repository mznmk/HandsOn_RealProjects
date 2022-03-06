/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:39:08 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 15:43:57 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fifteen_puzzle.h"

extern t_envs	e;
extern t_vars	v;

/**
 * @brief 	allocate memory (grid)
 */
void			allocate_memory(void)
{
	// [ variables ]
	int		*grid;

	// [ allocate memory ]
	v.grid = NULL;
	// allocate memory
	grid = (int *)malloc(sizeof(int) * e.cell_size);
	if (!grid)
		exit_game();
	// set allocated memory
	v.grid = grid;
}

/**
 * @brief	deallocate memory (grid)
 */
void			deallocate_memory(void)
{
	// [ deallocate memory ]
	if (v.grid)
		free(v.grid);
}
