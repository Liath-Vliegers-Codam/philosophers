/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_dining_table.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:33:50 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/21 13:33:50 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	choose_forks(t_philosopher *phil, t_table *table)
{
	if (phil->id % 2 == 0)
	{
		phil->fork_r = &(table->forks[phil->id - 1]);
		phil->fork_l = &(table->forks[(phil->id) % table->philo_count]);
	}
	else
	{
		phil->fork_r = &(table->forks[(phil->id) % table->philo_count]);
		phil->fork_l = &(table->forks[phil->id - 1]);
	}
}

bool	init_philosopher(t_table *table)
{
	int				i;
	t_philosopher	*philos;

	philos = (t_philosopher *)malloc \
	(sizeof(t_philosopher) * table->philo_count);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].t_last_meal_ms = 0;
		philos[i].done_eating = false;
		philos[i].table = table;
		choose_forks(&philos[i], table);
		if (pthread_mutex_init(&(philos[i].phil_mutex), NULL) != 0)
		{
			clean_philos(philos, i);
			return (false);
		}
		i++;
	}
	table->philos = philos;
	return (true);
}

bool	init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc \
	(sizeof(pthread_mutex_t) * table->philo_count);
	if (!forks)
		return (false);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			clean_forks(forks, i);
			return (false);
		}
		i++;
	}
	table->forks = forks;
	return (true);
}

bool	set_dining_table(t_table *table)
{
	if (!init_forks(table))
	{
		return (false);
	}
	if (!init_philosopher(table))
	{
		clean_forks(table->forks, table->philo_count);
		return (false);
	}
	if (pthread_mutex_init(&(table->table_mutex), NULL) != 0)
	{
		clean_forks(table->forks, table->philo_count);
		clean_philos(table->philos, table->philo_count);
		return (false);
	}
	if (pthread_mutex_init(&(table->print_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&(table->table_mutex));
		clean_forks(table->forks, table->philo_count);
		clean_philos(table->philos, table->philo_count);
		return (false);
	}
	return (true);
}
