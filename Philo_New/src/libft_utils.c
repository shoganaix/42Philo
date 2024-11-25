/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:17:49 by msoriano          #+#    #+#             */
/*   Updated: 2024/11/04 19:33:16 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_perror(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + sign * (str[i] - '0');
		i++;
	}
	return (number);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
