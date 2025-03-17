/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:33:41 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/21 13:33:41 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (!init_args(argc, argv, &table))
	{
		return (1);
	}
	if (!set_dining_table(&table))
	{
		return (2);
	}
	if (!start_dinner(&table))
	{
		clear_dining_table(&table);
		return (3);
	}
	clear_dining_table(&table);
	return (0);
}
