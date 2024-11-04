/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:11:11 by msoriano          #+#    #+#             */
/*   Updated: 2024/11/04 19:31:57 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>

# define RESET		"\x1b[0m"
# define BLACK		"\x1b[30m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1b[37m"

typedef struct s_philo
{
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
	int				eat_counter;
	pthread_t		thread_id;
	struct s_data	*data;
	long long		time_of_last_meal;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	int				dead; //bool protect
	int				finished_eating; //bool protect
	t_philo			philosophers[200];
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	long long		time_of_death;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	lock_meal; // eat_counter protection
	pthread_mutex_t	lock_wr;
	pthread_mutex_t	dead_lock; //Not sure if necessary
}	t_data;

/*Libft utils*/
void		my_perror(char *msg);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_isspace(char c);

/*Utils*/
long long	get_timestamp(void);
void		prints(t_data *data, int id, char *message);
void		clears_and_exit(t_data *data, t_philo *philo);
void		ft_usleep(int time, t_data *data);
long long	get_now(t_data *data);

/*Checks*/
int			check_input(char **argv);
int			check_non_negative(char **argv);
void		check_death(t_data *data, t_philo *philo);
void		print_values(t_data *data);

/*Philo*/
void		take_forks(t_philo *philo);
void		*routine(void *philo);
void		action_eat(t_philo *philo);

/*Main*/
int			init_mutex(t_data *data);
int			init_philos(t_data *data);
int			thread_init(t_data *data);
int			init_values(t_data *data, char **argv);

#endif

/*
ARGUMENTOS QUE RECIBIRA EL PROGRAMA:
		◦ number_of_philosophers: number of philosophers and forks.
		◦ time_to_die (milisecs): if a philosopher doesnt start eating in 
			'time_to_die' after STARTING his last meal or the beginning, 
			they'll die.
		◦ time_to_eat (milisecs): time it takes a philosopher to eat. 
				During that time he will use and lock two forks.
		◦ time_to_sleep (milisecs): time a philosopher will spend sleeping.
		◦ number_of_times_each_philosopher_must_eat (optional): 
			if all philosophers eat at least 
			'number_of_times_each_philosopher_must_eat' the program ends
				If not specified, the simulation will stop only at 
					the death of a philosopher.
CAMBIOS DE ESTADO:
		◦ timestamp_in_ms X has taken a fork
		◦ timestamp_in_ms X is eating
		◦ timestamp_in_ms X is sleeping
		◦ timestamp_in_ms X is thinking
		◦ timestamp_in_ms X died
*/
