/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 11:57:18 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_regular_status(t_data *data, const int philo_id,
								const int message_len, const char *message)
{
	sem_wait(data->sem_stdout);
	if (data->first_death_report == false)
	{
		ft_putnbr(STDOUT_FILENO, data->philo_state_time_stamp[philo_id]);
		ft_putnbr(STDOUT_FILENO, (unsigned long)philo_id);
		ft_put_message_fd(STDOUT_FILENO, (size_t)message_len, message);
	}
	sem_post(data->sem_stdout);
}

void	put_death_status(t_data *data, const int philo_id)
{
	static bool	already_reported_flag;

	if (already_reported_flag == false)
	{
		sem_wait(data->sem_stdout);
		if (already_reported_flag == false)
		{
			already_reported_flag = true;
			ft_putnbr(STDOUT_FILENO, get_death_time(data, philo_id));
			ft_putnbr(STDOUT_FILENO, (unsigned long)philo_id);
			ft_put_message_fd(STDOUT_FILENO, LEN_IS_DEAD, MESSAGE_DEAD);
		}
		sem_post(data->sem_stdout);
	}
}