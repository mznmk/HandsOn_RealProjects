/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 04:59:20 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 07:13:46 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern int errno;

int     kbhit(void)
{
	fd_set          rfd;
	struct timeval  timeout = {0, 0};
	FD_ZERO(&rfd);
	FD_SET(0, &rfd);    // 0:stdin
	int ret = select(1, &rfd, NULL, NULL, &timeout);
	if (ret == 1)
		return 1;
	else
		return 0;
}

int     getch(void)
{
	unsigned char   c;
	int             n;
	while ((n = read(0, &c, 1)) < 0 && errno == EINTR)
		;
	if (n == 0)
		return -1;
	else
		return (int)c;
}

static void    onsignal(int sig)
{
	signal(sig, SIG_IGN);
	switch (sig)
	{
	case SIGINT:
	case SIGQUIT:
	case SIGTERM:
	case SIGHUP:
		exit(1);
		break;    
	}
	return;
}

int     tinit(t_vars *v)
{
	if(tcgetattr(1, &v->otty) < 0)
		return -1;
	v->ntty = v->otty;
	v->ntty.c_iflag &= ~(INLCR|ICRNL|IXON|IXOFF|ISTRIP);
	v->ntty.c_oflag &= ~OPOST;
	v->ntty.c_lflag &= ~(ICANON|ECHO);
	v->ntty.c_cc[VMIN] = 1;
	v->ntty.c_cc[VTIME] = 0;
	tcsetattr(1, TCSADRAIN, &v->ntty);
	signal(SIGINT, onsignal);
	signal(SIGQUIT, onsignal);
	signal(SIGTERM, onsignal);
	signal(SIGHUP, onsignal);
	return 0;
}

int		tfinal(t_vars *v)
{
	tcsetattr(1, TCSADRAIN, &v->otty);
	write(1, "\n", 1);
	return 0;
}