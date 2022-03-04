/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 16:32:56 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 02:36:31 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

/**
 * @brief 	allocate memory (field)
 * @return	none
 */
void			allocate_memory(void)
{
	// [ variables ]
	t_cell		*field;
	int			size;

	// [ allocate memory ]
	// allocate memory
	size = e.field_size.height * e.field_size.width;
	field = (t_cell *)malloc(sizeof(t_cell) * size);
	if (!field)
		exit_tetris();
	// set allocated memory
	v.field = field;
}

/**
 * @brief	deallocate memory (field)
 * @return 	none
 */
void			deallocate_memory(void)
{
	// [ deallocate memory ]
	if (v.field)
		free(v.field);
}

/**
 * @brief	convert field coord (2D->1D)
 * @param	y		coord y
 * @param	x		coord x
 * @return	field index
 */
int				conv_field_coord(int y, int x)
{
	// [ return ]
	return e.field_size.width * y + x;
}
