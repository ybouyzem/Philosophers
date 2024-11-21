/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 06:07:33 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/21 14:30:30 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void leaks()
{
	system("leaks philo");
}

int	check_is_num(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) && str[i])
		i++;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	while (ft_isspace(str[i]) && str[i])
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	check_args(char **argv)
{
	if (check_is_num(argv[1]) || ft_atoi(argv[1]) <= 0)
		return (write(2, "invalid philsophers's number!\n", 29), 1);
	if (check_is_num(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (write(2, "invalid time_to_die's number!\n", 29), 1);
	if (check_is_num(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (write(2, "invalid time_to_eat's number!\n", 29), 1);
	if (check_is_num(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (write(2, "invalid time_to_sleep's number!\n", 29), 1);
	if (argv[5] && (check_is_num(argv[5]) || ft_atoi(argv[5]) <= 0))
	{
		if (ft_atoi(argv[5]) == 0)
			return (1);
		return (write(2, "invalid times_each_philo_must_eat number!\n", 29), 1);
	}
	return (0);
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