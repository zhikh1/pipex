/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 15:01:05 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	new = (char *)malloc((len + 1) * sizeof(char));
	while (len >= 0 && new)
	{
		new[len] = str[len];
		len--;
	}
	return (new);
}
