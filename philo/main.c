/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 06:07:33 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/10 01:20:38 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void leaks()
{
	system("leaks philo");
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
	while (++i < program->num_of_philos)
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
	init_program(&program, philos, forks, argv);
	simulation(&program, philos);
	return (0);
}