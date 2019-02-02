/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:54:58 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/02 21:37:26 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define BUFF_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"

int		*ft_dec_to_bin(int dec);
int		ft_bin_to_dec(int *bin);
int		ft_ping_getset(int mode, int pid);
void	ft_pong_handler(int sig, siginfo_t *info, void *context);
void	ft_handle_pong(void);

#endif
