/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:00 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 13:21:12 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		update_current_time(t_data *data)
{
	static unsigned long		origin_time;
	static unsigned long		current_time;
	static struct timeval		time;

	usleep(250);
	gettimeofday(&time, NULL);
	current_time = (unsigned long)(time.tv_sec * 1000)
					+ (unsigned long)(time.tv_usec / 1000);
	if (origin_time == 0)
		origin_time = current_time;
	data->current_clock = current_time - origin_time;
}

void		*clock_routine(void *data_arg)
{
	t_data						*data;

	data = (t_data *)data_arg;
	while (data->done_report_flag == false && data->death_report == false)
		update_current_time(data);
	if (data->death_report == true)
		exit(CHILD_IS_DEAD);
	return (NULL);
}
