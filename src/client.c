/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:53:27 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/03 17:00:00 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_char(pid_t pid, int *bin)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		if (bin[i] == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putendl_fd("An error occured while sending bit '0'.", 2);
				exit(1);
			}
		}
		if (bin[i] == 1)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_putendl_fd("An error occured while sending bit '1'.", 2);
				exit(1);
			}
		}
		usleep(150);
		++i;
	}
}

static int	ft_send_text(pid_t pid, char *text)
{
	int		i;

	i = 0;
	while (text[i] != '\0')
	{
		ft_send_char(pid, ft_dec_to_bin((int)text[i]));
		++i;
	}
	ft_send_char(pid, ft_dec_to_bin((int)'\0'));
	return (0);
}

int			main(int ac, char **av)
{
	pid_t	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid == 0 || pid == -1)
			ft_putendl_fd("Invalid PID", 2);
		else
			return (ft_send_text(pid, av[2]));
	}
	else
		ft_putendl_fd("Usage: ./client PID message", 2);
	return (1);
}
