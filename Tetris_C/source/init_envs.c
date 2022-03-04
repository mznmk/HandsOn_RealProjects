/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:48:55 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 08:36:23 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_envs	e;

static void		get_terminal_size(void)
{
	// [ variables ]
	struct winsize	ws;

	// [ get terminal size ]
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1)
	{
		if (0 < ws.ws_col)
			e.term_size.width = (int)ws.ws_col - 1;
		if (0 < ws.ws_row)
			e.term_size.height = (int)ws.ws_row - 1;
	}
}

static void		set_aveilable_field_size_range(void)
{
	// [ set field_size (min) ]
	e.field_size_min.height = NEXT_HEIGHT * 2 + SCORE_HEIGHT + 2;
	e.field_size_min.width = BLOCK_SIZE;

	// [ set field_size (max) ]
	e.field_size_max.height = e.term_size.height - 2;
	e.field_size_max.width = e.term_size.width / 2 - NEXT_WIDTH  - 2;
}

static void		set_field_size(int argc, char **argv)
{
	// [ set field size ]
	int field_height = e.term_size.height;
	int field_width = e.term_size.width;
	if (2 <= argc)
	{
		field_height = atoi(argv[1]);
		field_width = atoi(argv[2]);
	}
	// height
	if ((e.field_size_min.height <= field_height) &&
		(field_height <= e.field_size_max.height))
		e.field_size.height = field_height;
	else
		e.field_size.height = e.field_size_max.height;
	// width
	if ((e.field_size_min.width <= field_width) &&
		(field_width <= e.field_size_max.width))
		e.field_size.width = field_width;
	else
		e.field_size.width = e.field_size_max.width;
}

static void		set_size(int argc, char **argv)
{
	// [ get terminal size ]
	get_terminal_size();

	// [ set aveilable field size range ]
	set_aveilable_field_size_range();

	// [ set field size ]
	set_field_size(argc, argv);

	// [ set next size ]
	e.next1_size.height = NEXT_HEIGHT;
	e.next1_size.width = NEXT_WIDTH;
	e.next2_size.height = NEXT_HEIGHT;
	e.next2_size.width = NEXT_WIDTH;

	// [ set score size ]
	e.score_size.height = SCORE_HEIGHT;
	e.score_size.width = SCORE_WIDTH;

	// [ set back size ]
	e.back_size.height = e.field_size.height + 2;
	e.back_size.width = e.field_size.width + e.next1_size.width + 3;
}

// -------------------------------------------------------------------------- //

static void		set_coord(void)
{
	// [ set back coord ]
	e.back_coord.y = 0;
	e.back_coord.x = 0;

	// [ set field coord ]
	e.field_coord.y = 1;
	e.field_coord.x = 1;

	// [ set next coord ]
	e.next1_coord.y = e.field_coord.y;
	e.next1_coord.x = e.field_coord.x + e.field_size.width + 1;
	e.next2_coord.y = e.next1_coord.y + e.next1_size.height + 1;
	e.next2_coord.x = e.next1_coord.x;

	// [ set score coord ]
	e.score_coord.y = e.next2_coord.y + e.next2_size.height + 1;
	e.score_coord.x = e.next2_coord.x;

	// [ set start coord ]
	e.start_coord.y = 0;
	e.start_coord.x = e.field_size.width / 2 - 2;
}

// -------------------------------------------------------------------------- //

static void		set_param_fall_speed_up(int argc, char **argv)
{
	// [ set fall speed ]
	int		rate;
	rate = 0;
	if (3 < argc)
		rate = atoi(argv[3]);
	if (FALL_SPEED_MIN <= rate && rate <= FALL_SPEED_MAX)
		v.fall_speed = FALL_SPEED_BASE * rate;
	else
		v.fall_speed = FALL_SPEED_BASE * (FALL_SPEED_MIN + FALL_SPEED_MAX) / 2;
}

static void		set_param(int argc, char **argv)
{
	// [ set score ]
	v.score = 0;
	// [ block_now coord ]
	v.prev_y = 0;
	v.prev_x = 0;
	v.now_y = e.start_coord.y;
	v.now_x = e.start_coord.x;
	// [ fall_time ]
	v.fall_time_max = FALL_TIME_MAX;
	// [ fall speed ]
	set_param_fall_speed_up(argc, argv);
}
// -------------------------------------------------------------------------- //

void			init_envs(int argc, char **argv)
{
	// [ set field/next/score/back size ]
	set_size(argc, argv);
	// [ set field/next/score/back/start coord ]
	set_coord();
	// [ set game parameter ]
	set_param(argc, argv);
}