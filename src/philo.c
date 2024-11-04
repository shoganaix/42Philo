/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:36:17 by msoriano          #+#    #+#             */
/*   Updated: 2024/11/04 19:36:12 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	prints(philo->data, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	prints(philo->data, philo->philo_id, "has taken a fork");
}

void	action_eat(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	take_forks(philo);
	pthread_mutex_lock(&(data->lock_meal));
	prints(philo->data, philo->philo_id, "is eating");
	philo->time_of_last_meal = get_now(data);
	pthread_mutex_unlock(&(data->lock_meal));
	ft_usleep(data->time_to_eat, data);
	philo->eat_counter++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
}

void	*routine(void *philo_pt)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) philo_pt;
	data = philo->data;
	if (philo->philo_id % 2)
		usleep(150);
	while (!(data->dead))
	{
		action_eat(philo);
		if (data->finished_eating)
			break ;
		prints(data, philo->philo_id, "is sleeping");
		ft_usleep(data->time_to_sleep, data);
		prints(data, philo->philo_id, "is thinking");
	}
	return (NULL);
}
