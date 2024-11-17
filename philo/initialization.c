/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 05:58:16 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/16 18:32:07 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	allocate_utils(t_philo **philo, pthread_mutex_t **forks, t_program program)
{
	(*philo) = (t_philo *)malloc(sizeof(t_philo) * program.num_of_philos);
	if (!(*philo))
		return (1);
	(*forks) = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * program.num_of_philos);
	if (!(*forks))
	{
		free(*philo);
		return (1);
	}
	return (0);
}

int	init_philos(t_program *program, t_philo *philos, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < program->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[program->num_of_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		philos[i].program = program;
		i++;
	}
	return (0);
}

int	init_forks(pthread_mutex_t *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_program(t_program *program, t_philo **philos, pthread_mutex_t **forks, char **argv)
{
	int	i;

	i = 0;
	program->dead_flag = 0;
	program->num_of_philos = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		program->required_meals = ft_atoi(argv[5]);
	else
		program->required_meals = -1;
	program->dead_flag = 0;
	pthread_mutex_init(&program->monitor_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
    if (allocate_utils(philos, forks, *program))
        return (1);
	init_forks(*forks, program);
	init_philos(program, *philos, *forks);
	return (0);
}
