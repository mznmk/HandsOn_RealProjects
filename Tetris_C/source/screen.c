/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:07:13 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 07:03:32 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

void	init_screen(t_vars *v)
{
	tinit(v);
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_field();
	cursol_off();
	return;
}

void	reset_screen(t_vars *v)
{
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_field();
	cursol_on();
	tfinal(v);
	return;
}
