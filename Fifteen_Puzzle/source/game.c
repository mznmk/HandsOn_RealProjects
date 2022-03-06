/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:11:12 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 15:57:59 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fifteen_puzzle.h"

extern t_envs	e;
extern t_vars	v;

static int		choose_random(int size)
{
	// [ return ]
	return rand() % size;
}

static void		set_random_color(void)
{
	int		rnd;
	// [ set char color ]
	set_char_color(CLR_BLACK);
	// [ set back color ]
	do
		rnd = choose_random(8);
	while (rnd == CLR_BLACK);
	set_back_color(rnd);
}

void			draw_back(void)
{
	// [ draw back ]
	set_random_color();
	set_attribute(ATR_BLIGHT);
	for (int i = 0; i < e.back_size.height; i++)
		for (int j = 0; j < e.back_size.width; j++)
		{
			set_position(e.back_coord.y + i,e.back_coord.x + j);
			printf("##");
			fflush(stdout);
		}
	set_char_color(CLR_DEFAULT);
	set_back_color(CLR_DEFAULT);
	set_attribute(ATR_NORMAL);
}