/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:04 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/15 11:14:46 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			*philo_monitor(void *i_arg)
{
	bool			alive;
	int				philo_id;
	t_data			*data;
	unsigned long	time;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	// time = get_current_time();
	time = 0;
	alive = false;
	pthread_mutex_lock(&data->mutex_race_starter);
	pthread_mutex_unlock(&data->mutex_race_starter);
	while ((alive = (int)time - (int)data->last_meal[philo_id] <= data->param[T_TO_DIE]) == true
								&& data->first_death_report == false
								&& data->done_report_flag[philo_id] == false)
		time = get_current_time();
	if (data->first_death_report == false && alive == false)
	{
		pthread_mutex_lock(&data->mutex_death_report);
		data->first_death_report = true;
		data->first_death_report_timestamp = time;
		put_death_status(data, philo_id);
		pthread_mutex_unlock(&data->mutex_death_report);
	}
	pthread_exit(NULL);
}





















		// dprintf(STDERR_FILENO, "MONITOR %ld ....... %d .............%ld...............WAITING\n", get_current_time(), philo_id, data->last_meal[philo_id]);
		// dprintf(STDERR_FILENO, "MONITOR %ld ....... %d .............%ld..................GO\n", get_current_time(), philo_id, data->last_meal[philo_id]);
