/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:36:17 by msoriano          #+#    #+#             */
/*   Updated: 2024/11/25 17:44:24 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * 
 * 
 */
int	philocontinues(t_data *data)
{
	pthread_mutex_lock(&(data->lock_meal));
	if (!(data->dead) && (!data->finished_eating))
	{
		pthread_mutex_unlock(&(data->lock_meal));
		return (1);
	}
	pthread_mutex_unlock(&(data->lock_meal));
	return (0);
}

/**
 * Locks the second fork for the philosopher and prints a message
 */
int	lock_second_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->philo_id % 2 == 0)
	{
		if (pthread_mutex_lock(&(data->forks[philo->left_fork_id])) != 0)
			return (pthread_mutex_unlock(&(data->forks[philo->right_fork_id]))
				, 1);
		if (philocontinues(data))
			prints(philo->data, philo->philo_id, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(&(data->forks[philo->right_fork_id])) != 0)
			return (pthread_mutex_unlock(&(data->forks[philo->left_fork_id]))
				, 1);
		if (philocontinues(data))
			prints(philo->data, philo->philo_id, "has taken a fork");
	}
	return (0);
}

/**
 * Handles the process of taking forks for a philosopher
 *
 * 		 It first checks the case where there is only one philo
 * 
 *		 For multiple philosophers, it locks the first fork based on 
 *       	the philo's ID, prints a message, and then calls lock_second_fork()
 */
int	take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->number_of_philosophers == 1)
	{
		ft_usleep(data->time_to_die, data);
		return (1);
	}
	if (philo->philo_id % 2 == 0)
		pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	else
		pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	if (philocontinues(data))
		prints(philo->data, philo->philo_id, "has taken a fork");
	return (lock_second_fork(philo));
}

/**
 *  Handles eating action; including fork handling, timing and eat_counter
 */
void	action_eat(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	if (!take_forks(philo))
	{
		prints(philo->data, philo->philo_id, "is eating");
		pthread_mutex_lock(&(data->lock_meal));
		philo->time_of_last_meal = get_now(data);
		philo->eat_counter++;
		pthread_mutex_unlock(&(data->lock_meal));
		ft_usleep(data->time_to_eat, data);
		pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
	}
	else
		return ;
}

/**
 * Routine for philosopher/thread actions: eating, sleeping, and thinking
 * 
 *  Note:
 * 	   -> if (philo->philo_id % 2)
	   -> usleep(150);
 *
 *  This lines were used to introduce a slight delay for odd-numbered philos
 *  This prevents deadlocks when philos try to pick up forks simultaneously
 *  This logic has been moved to function take_forks()
 */
void	*routine(void *philo_pt)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) philo_pt;
	data = philo->data;
	while (philocontinues(data))
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
