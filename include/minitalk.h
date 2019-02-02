/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:54:58 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/02 15:55:00 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define BUFF_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"

int *ft_dec_to_bin(int ci);
int ft_bin_to_dec(int *b);

#endif
