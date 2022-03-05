/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tetris.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:56:39 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 11:43:10 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_envs	e;

/**
 * @brief		attach event to signal
 * @param sig	signal
 */
static void		handle_signal(int sig)
{
	// [ attach event to signal ]
	switch (sig)
	{
		case SIGINT:
		case SIGQUIT:
		case SIGTERM:
		case SIGHUP:
			exit_tetris();
			break;    
	}
}

/**
 * @brief		save terminal setting (termcap)
 * @return		status
 */
static int		init_term(void)
{
	// [ save terminal setting ]
	if(tcgetattr(1, &e.otty) < 0)
		return -1;
	e.ntty = e.otty;
	e.ntty.c_iflag &= ~(INLCR|ICRNL|IXON|IXOFF|ISTRIP);
	e.ntty.c_oflag &= ~OPOST;
	e.ntty.c_lflag &= ~(ICANON|ECHO);
	e.ntty.c_cc[VMIN] = 1;
	e.ntty.c_cc[VTIME] = 0;
	tcsetattr(1, TCSADRAIN, &e.ntty);

	// [ return ]
	return 0;
}

/**
 * @brief		initialize tetris
 * @return		none
 */
void			init_tetris(int argc, char **argv)
{
	// [ initialize environment variables ]
	init_envs(argc, argv);

	// [ allocate memory (field) ]
	allocate_memory();

	// [ initialize tetris variables ]
	init_vars();
	
	// [ save terminal config (termcap) ]
	if (init_term() != 0)
		deallocate_memory();

	// [ set signal ]
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGHUP, handle_signal);

	// [ set terminal config ]
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_terminal();
	cursol_off();
}
