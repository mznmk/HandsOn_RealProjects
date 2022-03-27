/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:54:10 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/27 20:54:20 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bomberman.h"

extern t_vars	v;

bool			is_in_map(int y, int x)
{
	if (y < 0 || MAP_HEIGHT <= y)
		return false;
	if (x < 0 || MAP_WIDTH <= x)
		return false;
	return true;
}

bool			is_hard_block(int y, int x)
{
	if (v.map[y][x] == HARD_BLOCK)
		return true;
	return false;
}

bool			is_player(int y, int x)
{
	if (v.player.y == y && v.player.x == x)
		return true;
	return false;
}

bool			is_enemy(int y, int x)
{
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (v.enemy[i].y == y &&
			v.enemy[i].x == x &&
			0 < v.enemy[i].life)
			return true;
	}
	return false;
}

bool			is_softblock(int y, int x)
{
	for (int i = 0; i < SOFTBLOCK_COUNT; i++) {
		if (v.softblock[i].y == y &&
			v.softblock[i].x == x &&
			0 < v.softblock[i].life)
			return true;
	}
	return false;
}

bool			is_door(int y, int x)
{
	if (v.door.y == y && v.door.x == x)
		return true;
	return false;
}
