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
