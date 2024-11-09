/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 06:07:33 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/09 06:09:20 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void leaks()
{
	system("leaks philo");
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
	return (0);
}