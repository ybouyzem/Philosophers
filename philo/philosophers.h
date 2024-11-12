/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:17:07 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/11 06:55:33 by ybouyzem         ###   ########.fr       */
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

# define LFORK 0
# define RFORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DEAD 5


typedef struct s_program
{
	int             num_of_philos;
	int				required_meals;
	int             dead_flag;
	size_t          time_to_die;
	size_t          time_to_eat;
	size_t          time_to_sleep;
	pthread_t	   monitor;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t write_lock;
} t_program;

typedef struct s_philo
{
	pthread_t       thread;
	int             id;
	int             meals_eaten;
	int			    is_finished;
	size_t          last_meal;
	size_t          start_time;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	t_program       *program;
} t_philo;


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
int	init_program(t_program *program, t_philo **philos, pthread_mutex_t **forks, char **argv);
size_t	get_current_time();
void    *ft_monitor(void    *arg);
void    *ft_philo(void    *arg);
void my_sleep(size_t time, t_philo *philo);
int is_dead(t_philo *philo);
int	is_holding_forks(t_philo *philo);
void	printer(t_philo *philo, int mode);
void	eating(t_philo *philo);
#endif