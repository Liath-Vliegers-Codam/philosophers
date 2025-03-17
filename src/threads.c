/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:33:52 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/21 13:33:52 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	join_threads(t_table *table, int nbr)
{
	int	i;

	i = 0;
	if (nbr < table->philo_count)
		pthread_mutex_unlock(&(table->table_mutex));
	while (i < nbr)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

bool	create_threads(t_table *table)
{
	int	i;
	int	fail;

	i = 0;
	while (i < table->philo_count)
	{
		fail = pthread_create \
		(&(table->philos[i].thread), NULL, &routine, &(table->philos[i]));
		if (fail)
		{
			join_threads(table, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	start_dinner(t_table *table)
{
	int	i;

	if (table->times_to_eat == 0)
	{
		printf("All %d philos have eaten %d times\n", \
		table->philo_count, table->times_to_eat);
		return (true);
	}
	pthread_mutex_lock(&(table->table_mutex));
	if (!create_threads(table))
		return (false);
	usleep(table->philo_count * 10);
	table->start_time = gettimeofday_ms();
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].t_last_meal_ms = table->start_time;
		i++;
	}
	pthread_mutex_unlock(&(table->table_mutex));
	dinner_party(table);
	join_threads(table, table->philo_count);
	return (true);
}
