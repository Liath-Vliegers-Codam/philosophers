/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:49:18 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/28 19:02:22 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

uint64_t	gettimeofday_ms(void)
{
	static struct timeval	time;
	uint64_t				now;

	gettimeofday(&time, NULL);
	now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now);
}

uint64_t	timestamp_ms(uint64_t start)
{
	uint64_t		now;

	now = gettimeofday_ms();
	return (now - start);
}

bool	print_safely(t_philosopher *phil, char	*activity)
{
	pthread_mutex_lock(&phil->table->print_mutex);
	if (death_check(phil->table))
		return (pthread_mutex_unlock(&phil->table->print_mutex), false);
	printf("%04ld %d %s\n", \
	timestamp_ms(phil->table->start_time), phil->id, activity);
	pthread_mutex_unlock(&phil->table->print_mutex);
	return (true);
}

void	precise_usleep(long usec, t_table *table)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	while (1)
	{
		if (death_check(table))
			return ;
		gettimeofday(&now, NULL);
		if ((now.tv_sec - start.tv_sec) * 1000000 + \
		(now.tv_usec - start.tv_usec) >= usec)
		{
			break ;
		}
		usleep(250);
	}
}
