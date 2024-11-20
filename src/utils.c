/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:17:56 by msoriano          #+#    #+#             */
/*   Updated: 2024/11/20 15:59:01 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * Gets the current timestamp in milliseconds since the epoch.
 */
long long	get_timestamp(void)
{
	struct timeval	t_val;

	if (gettimeofday(&t_val, NULL))
		return (my_perror("gettimeofday() function failed \n"), -1);
	return ((t_val.tv_sec * 1000) + (t_val.tv_usec / 1000));
}

/**
 * Calculates the elapsed time since the simulation started
 */
long long	get_now(t_data *data)
{
	long long int	time;

	time = get_timestamp();
	return (time - data->start_time);
}

/**
 * Sleeps for the specified time in milliseconds, checking simulation conditions
 */
void	ft_usleep(int time, t_data *data)
{
	long long	start;

	start = get_timestamp();
	while (!(data->dead) && (!data->finished_eating))
	{
		if ((get_timestamp() - start) >= time)
			break ;
		usleep(50);
	}
}

/**
 *  Destroys mutex and clears data
 * NOT necessary to free thread_id because it points at philosophers pointer
 */
void	clears_and_exit(t_data *data, t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->lock_wr);
}

/**
 * This function safely prints a philo's status message
 * It handles thread_safe access to terminal using mutex (lock_wr)
 */
void	prints(t_data *data, int id, char *message)
{
	int			color_index;
	const char	*colors[6] = {MAGENTA, GREEN, CYAN, RED, YELLOW, BLUE};

	color_index = id % 6;
	pthread_mutex_lock(&(data->lock_wr));
	if (!(data->dead))
		printf("%s%lli %i %s" RESET "\n", colors[color_index],
			get_now(data), id + 1, message);
	pthread_mutex_unlock(&(data->lock_wr));
}
