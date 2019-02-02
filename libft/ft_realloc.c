/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:50:32 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/02 15:50:33 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_realloc(char *s, int size)
{
	char		*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s) + size));
	ft_strcpy(tmp, s);
	if (s != NULL)
		free(s);
	return (tmp);
}
