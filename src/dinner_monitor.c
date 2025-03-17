/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:33:38 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/21 13:33:38 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	all_courses_served(t_table *table)
{
	int		i;
	int		eat_count;
	bool	philo_done;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&(table->philos[i].phil_mutex));
		philo_done = table->philos[i].done_eating;
		eat_count = table->philos[i].eat_count;
		pthread_mutex_unlock(&(table->philos[i].phil_mutex));
		if (philo_done == true)
		{
			i++;
			continue ;
		}
		if (eat_count < table->times_to_eat)
			return (false);
		pthread_mutex_lock(&(table->philos[i].phil_mutex));
		table->philos[i].done_eating = true;
		pthread_mutex_unlock(&(table->philos[i].phil_mutex));
		i++;
	}
	return (true);
}

bool	death_check(t_table *table)
{
	bool		has_died;

	pthread_mutex_lock(&table->table_mutex);
	has_died = table->philo_died;
	pthread_mutex_unlock(&table->table_mutex);
	if (has_died == true)
	{
		return (true);
	}
	return (false);
}

bool	death_monitor(t_philosopher *phil)
{
	uint64_t	limit_ms;
	uint64_t	time_ms;

	if (death_check(phil->table))
		return (true);
	pthread_mutex_lock(&(phil->phil_mutex));
	limit_ms = phil->t_last_meal_ms + phil->table->t_die_ms;
	pthread_mutex_unlock(&(phil->phil_mutex));
	time_ms = gettimeofday_ms();
	if (limit_ms < time_ms)
	{
		pthread_mutex_lock(&phil->table->table_mutex);
		phil->table->philo_died = true;
		pthread_mutex_unlock(&phil->table->table_mutex);
		return (true);
	}
	return (false);
}

bool	philosopher_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (death_monitor(&(table->philos[i])))
		{
			pthread_mutex_lock(&table->print_mutex);
			printf("%04ld %d died\n", \
			timestamp_ms(table->start_time), table->philos[i].id);
			pthread_mutex_unlock(&table->print_mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

void	dinner_party(t_table *table)
{
	while (1)
	{
		usleep(1000);
		if (philosopher_died(table))
			return ;
		if (table->times_to_eat > 0 && all_courses_served(table))
		{
			pthread_mutex_lock(&table->table_mutex);
			table->philo_died = true;
			pthread_mutex_unlock(&table->table_mutex);
			printf("All %d philos have eaten %d times\n", \
			table->philo_count, table->times_to_eat);
			return ;
		}
	}
}
