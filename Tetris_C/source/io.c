/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 04:59:20 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 03:09:55 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_envs	e;

/**
 * @brief 
 * 
 * @return int 
 */
int     		kbhit(void)
{
	fd_set          rfd;
	struct timeval  timeout = {0, 0};
	FD_ZERO(&rfd);
	FD_SET(STDIN_FILENO, &rfd);
	int ret = select(1, &rfd, NULL, NULL, &timeout);
	if (ret == 1)
		return 1;
	else
		return 0;
}

unsigned long	getch(void)
{
	unsigned long   keycode;
	int             rtn;
	// while ((rtn = read(0, &keycode, 8)) < 0 && errno == EINTR)
	// 	;
	while (42)
	{
		keycode = 0UL;
		rtn = read(STDIN_FILENO, &keycode, 8);
		if (!(rtn < 0))// && errno == EINTR))
			break;
	} 
	if (rtn == 0)
		return -1;
	else
		return keycode;
}

static void    onsignal(int sig)
{
	// signal(sig, SIG_IGN);
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

int     		tinit(void)
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

	// [ set signal ]
	signal(SIGINT, onsignal);
	signal(SIGQUIT, onsignal);
	signal(SIGTERM, onsignal);
	signal(SIGHUP, onsignal);

	// [ return ]
	return 0;
}

/**
 * @brief 
 * 
 * @return int 
 */
int				tfinal(void)
{
	// [ load terminal setting ]
	tcsetattr(1, TCSADRAIN, &e.otty);
	write(1, "\n", 1);

	// [ return ]
	return 0;
}