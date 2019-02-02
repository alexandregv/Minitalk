/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 21:36:51 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/02 21:37:08 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		ft_ping_getset(int mode, int pid)
{
	static int	last_pid = 42;

	if (mode == 1)
		last_pid = pid;
	else
		return (last_pid);
	return (42);
}

void	ft_pong_handler(int sig, siginfo_t *info, void *context)
{
	ft_putstr("Pong from PID ");
	ft_putnbr(info->si_pid);
	ft_putendl(" !");
	(void)sig;
	(void)context;
}

void	ft_handle_pong(void)
{
	struct sigaction	action;

	action.sa_sigaction = ft_pong_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
}
