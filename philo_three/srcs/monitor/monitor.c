/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:04 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 15:48:14 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		process_death(t_data *data, int philo_id, unsigned long time)
{
	pid_t			pid;

	data->death_report = true;
	data->death_report_timestamp = time;
	pid = fork();
	if (pid == 0)
	{
		put_death_status(data, philo_id);
		exit (0);
	}
	else if (pid == FAILURE)
		put_death_status(data, philo_id);
	else
		exit(CHILD_IS_DEAD);
}

void			*philo_monitor(void *i_arg)
{
	bool			alive;
	int				philo_id;
	t_data			*data;
	unsigned long	time;
	int				t_to_die;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	alive = false;
	time = 0;
	t_to_die = data->param[T_TO_DIE];
	while ((alive =	(int)time - (int)data->last_meal <= t_to_die) == true
		&& data->done_report_flag == false)
		time = data->current_clock;
	if (alive == false && data->done_report_flag == false)
	{
		sem_wait(data->sem_stdout);
		process_death(data, philo_id, time);
	}
	return (NULL);
}
