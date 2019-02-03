/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:53:27 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/03 23:20:48 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_char(pid_t pid, int *bin)
{
	int		i;
	int		sig;

	i = 0;
	while (i < 8)
	{
		if (bin[i] == 0)
			sig = SIGUSR1;
		else if (bin[i] == 1)
			sig = SIGUSR2;
		if (kill(pid, sig) == -1)
		{
			ft_putendl_fd(sig == SIGUSR1
				? "An error occured while sending bit '0'."
				: "An error occured while sending bit '1'.", 2);
			exit(1);
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
