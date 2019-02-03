/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:53:42 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/03 14:30:27 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int						*g_binary;

static void	ft_print_header(void)
{
	pid_t		pid;

	pid = getpid();
	ft_putstr("You can now send messages with: ./client ");
	ft_putnbr(pid);
	ft_putendl(" \"message\"");
}

static char	*ft_decode_append(char *str, int *tmp)
{
	static int	i = 0;

	if (i > BUFF_SIZE)
		str = ft_realloc(str, sizeof(char) * (ft_strlen(str) + BUFF_SIZE));
	str[i++] = (char)ft_bin_to_dec(tmp);
	if ((char)ft_bin_to_dec(tmp) == '\0')
	{
		ft_putendl(str);
		i = 0;
		free(str);
		str = (char*)malloc(sizeof(char) * BUFF_SIZE);
	}
	g_binary = tmp;
	ft_bzero(g_binary, 8);
	return (str);
}

static void	ft_handle_sigusr(int sig)
{
	*g_binary++ = (sig == SIGUSR2);
}

int			main(void)
{
	int			i;
	int			*tmp;
	char		*str;

	i = 0;
	g_binary = (int*)(malloc(sizeof(int) * 8));
	str = (char*)malloc(sizeof(char) * BUFF_SIZE);
	ft_bzero(g_binary, 8);
	tmp = g_binary;
	ft_print_header();
	signal(SIGUSR1, ft_handle_sigusr);
	signal(SIGUSR2, ft_handle_sigusr);
	while (1)
	{
		if (i > 7)
		{
			str = ft_decode_append(str, tmp);
			i = 0;
		}
		pause();
		i++;
	}
	free(g_binary);
	free(str);
	return (0);
}
