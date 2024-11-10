/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:16:50 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/10 01:23:21 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (argv[5] && (check_is_num(argv[5]) || ft_atoi(argv[5]) < 0))
		return (write(2, "invalid times_each_philo_must_eat number!\n", 29), 1);
	return (0);
}

void    *ft_philo(void    *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		my_sleep(philo->program->time_to_eat, philo);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		usleep(philo->program->time_to_eat * 1000);
		usleep(philo->program->time_to_sleep * 1000);
	}
}





