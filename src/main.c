/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:38:32 by msoriano          #+#    #+#             */
/*   Updated: 2024/11/04 19:36:43 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
 * Initializes start time and creates threads for each philosopher
 THIS LINE : if (pthread_create(&(philo[i].thread_id), NULL,
				routine, &(philo[i])))
 EXPLANATION: 
	* This loop creates process separated for each philosopher (threads)
	* Every philosopher executes 
	* their own set of instructions (a routine) independently
 */

int	thread_init(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philosophers;
	data->start_time = get_timestamp();
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&(philo[i].thread_id), NULL,
				routine, &(philo[i])))
			return (my_perror("error: pthread_create failed!"), -1);
		philo[i].time_of_last_meal = get_now(data);
		i++;
	}
	check_death(data, philo);
	clears_and_exit(data, philo);
	return (0);
}

/*
 * If pthread_mutex_init fails (return value different to 0)  -> then, returns 1
 * Initialized mutex: write, meals and forks
 * We create a loop for each fork to mutex
 */

int	init_mutex(t_data *data)
{
	int				i;

	i = data->number_of_philosophers;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->lock_wr), NULL))
		return (1);
	if (pthread_mutex_init(&(data->lock_meal), NULL))
		return (1);
	return (0);
}

/**
 * Initialize values on our philo structure
 * Left Fork ID: Their Index.   
 * Right Fork ID: Index of the next philosopher. 
 * For the last philosopher, the right fork ID wraps around to 0.
*/
int	init_philos(t_data *data)
{
	int		i;

	i = data->number_of_philosophers;
	while (--i >= 0)
	{
		data->philosophers[i].data = data;
		data->philosophers[i].philo_id = i;
		data->philosophers[i].left_fork_id = i;
		data->philosophers[i].right_fork_id = (i + 1)
			% (data->number_of_philosophers);
		data->philosophers[i].time_of_last_meal = get_timestamp();
		data->philosophers[i].eat_counter = 0;
	}
	return (0);
}

/**
 * Initialize values on our data structure and calls init_philos
*/
int	init_values(t_data *data, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	data->finished_eating = 0;
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (init_mutex(data) || init_philos(data))
		return (1);
	// print_values(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (my_perror("error: wrong number of arguments!"), -1);
	else if (check_input(argv) != 0)
		return (my_perror("error: not a valid argument!"), -1);
	else if (init_values(&data, argv) != 0)
		return (my_perror("error: initialization failed!"), -1);
	else if (thread_init(&data) != 0)
		return (my_perror("error: thread_init failed!"), -1);
	return (0);
}
// WE NEED TO THINK ABOUT ONLY ONE PHILO CASE
// int	case_one(t_data *data)
// {
// 	data->start_time = get_time();
// 	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
// 		return (error(TH_ERR, data));
// 	pthread_detach(data->tid[0]);
// 	while (data->dead == 0)

// 		ft_usleep(0, data);
// 	ft_exit(data);
// 	return (0);
// }