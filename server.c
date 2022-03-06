/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asallahi <asallahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:13:36 by asallahi          #+#    #+#             */
/*   Updated: 2022/03/05 19:57:40 by asallahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

void	handler(int signum, struct __siginfo *info, void *vo)
{
	static int	bit = 0;
	static char	c = 0xFF;
	static int	pid = 0;

	(void)*vo;	
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		c = 0xFF;
		bit = 0;
	}
	if (signum == SIGUSR1)
		c |= 128 >> bit;
	else
		c ^= 128 >> bit;
	if (++bit == 8)
	{
		ft_putchar(c);
		bit = 0;
		c = 0xFF;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 1 || av[1] != NULL)
	{
		ft_putstr("error\n");
	}
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	ft_putnbr(getpid());
	ft_putchar('\n');
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}
