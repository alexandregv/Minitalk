/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:53:27 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/03 18:08:39 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_retry(pid_t pid, int sig)
{
	static int	times = 0;

	ft_putstr_fd(C_RED"Retrying in 3 seconds", 2);
	sleep(1);
	ft_putchar_fd('.', 2);
	sleep(1);
	ft_putchar_fd('.', 2);
	sleep(1);
	ft_putchar_fd('.', 2);
	ft_putchar_fd('\n', 2);
	if (kill(pid, sig) == -1)
	{
		++times;
		if (times < 3)
			ft_retry(pid, sig);
		ft_putendl_fd(C_RED"Failed 3 times, quitting."C_NONE, 2);
		exit(1);
	}
}

static void	ft_send_char(pid_t pid, int *bin)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		if (bin[i] == 0)
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putendl_fd(C_RED"An error occured while sending bit '0'\
."C_NONE, 2);
				ft_retry(pid, SIGUSR1);
			}
		if (bin[i] == 1)
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_putendl_fd(C_RED"An error occured while sending bit '1'\
."C_NONE, 2);
				ft_retry(pid, SIGUSR2);
			}
		usleep(150);
		++i;
	}
}

static int	ft_send_text(pid_t pid, char *s)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] && s[i + j] == s[i])
			++j;
		ft_send_char(pid, ft_dec_to_bin(j));
		ft_send_char(pid, ft_dec_to_bin((int)s[i]));
		i += j;
	}
	ft_send_char(pid, ft_dec_to_bin(1));
	ft_send_char(pid, ft_dec_to_bin((int)'\0'));
	return (0);
}

int			main(int ac, char **av)
{
	pid_t	pid;

	ft_handle_pong();
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid == 0 || pid == -1)
			ft_putendl_fd(C_RED"Invalid PID"C_NONE, 2);
		else
			return (ft_send_text(pid, av[2]));
	}
	else
		ft_putendl_fd(C_RED"Usage: ./client PID message"C_NONE, 2);
	return (1);
}
