/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:17:07 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/09 06:08:27 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_philo
{
	pthread_t       thread;
	int             id;
	int             meals_eaten;
	size_t          last_meal;
	size_t          start_time;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
} t_philo;

typedef struct s_program
{
	int				required_meals;
	int             dead_flag;
	size_t          time_to_die;
	size_t          time_to_eat;
	size_t          time_to_sleep;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t write_lock;
	int             num_of_philos;
	t_philo 		*philos;
} t_program;


int     ft_isdigit(char c);
int ft_isspace(char c);
int	check_args(char **argv);
int	check_is_num(char *str);
int     ft_atoi(char *str);
int	init_forks(pthread_mutex_t *forks, t_program *program);
int	init_philos(t_program *program, t_philo *philos, pthread_mutex_t *forks);
int	check_args(char **argv);
int	init_forks(pthread_mutex_t *forks, t_program *program);
int	allocate_utils(t_philo **philo, pthread_mutex_t **forks, t_program program);
int	init_program(t_program *program, t_philo *philos, pthread_mutex_t *forks, char **argv);
size_t	get_current_time();

#endif