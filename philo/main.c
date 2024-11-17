/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 06:07:33 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/17 12:29:49 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void leaks()
{
	system("leaks philo");
}

void	print_philo(t_philo *philo)
{
	printf("philo id %d\n", philo->id);
	printf("philo meals_eaten %d\n", philo->meals_eaten);
	printf("philo last_meal %zu\n", philo->last_meal);
	printf("philo start_time %zu\n", philo->start_time);
	printf("philo left_fork %p\n", philo->left_fork);
	printf("philo right_fork %p\n", philo->right_fork);
	printf("philo program %p\n", philo->program);
}

void    simulation(t_program *program, t_philo *philos)
{
	int i;
	i = 0;
	if (pthread_create(&program->monitor, NULL, ft_monitor, philos))
		return ;
	while (i < program->num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, ft_philo, &philos[i]))
			return ;
		i++;
	}
	if (pthread_join(program->monitor, NULL))
		return ;
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			return ;
		i++;
	}		
}

int main(int argc, char **argv)
{
	t_program program;
	t_philo *philos;
	pthread_mutex_t *forks;
	
	
	if (argc < 5 || argc > 6)
		return (write(2, "invalid number of arguments!\n", 30), 1);
	if (check_args(argv))
		return (1);
	init_program(&program, &philos, &forks, argv);
	simulation(&program, philos);
	return (0);
}