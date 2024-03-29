/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_action_handlers.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/19 11:07:01 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_nb_meals_reached(t_data *data, const int philo_id)
{
	return (data->param[NB_MEALS] != UNSET
				&& data->nb_meals_eaten[philo_id] >= data->param[NB_MEALS]);
}

static bool	is_done_sleeping(t_data *data, unsigned long fell_asleep_timestamp)
{
	unsigned long	time_to_sleep;

	time_to_sleep = (unsigned long)data->param[T_TO_SLEEP] / 1000;
	return (data->current_clock - fell_asleep_timestamp >= time_to_sleep);
}

static bool	is_done_eating(t_data *data, int philo_id)
{
	unsigned long	time_to_eat;

	time_to_eat = (unsigned long)data->param[T_TO_EAT] / 1000;
	return (data->current_clock - data->last_meal[philo_id] >= time_to_eat
		|| data->first_death_report == true);
}

t_state		take_forks_and_eat_handler(t_data *data, const int philo_id)
{
	unsigned long	fell_asleep_timestamp;

	acquire_forks(data, philo_id);
	while (is_done_eating(data, philo_id) == false)
		usleep(1);
	data->philo_state_time_stamp[philo_id] = data->current_clock;
	drop_forks(data, philo_id);
	data->nb_meals_eaten[philo_id]++;
	if (is_nb_meals_reached(data, philo_id) == true)
		report_nb_meals_reached_and_exit_thread(data, philo_id);
	put_regular_status(data, philo_id, LEN_IS_SLEEPING, MESSAGE_SLEEPING);
	fell_asleep_timestamp = data->philo_state_time_stamp[philo_id];
	while (is_done_sleeping(data, fell_asleep_timestamp) == false)
		usleep(1);
	data->philo_state_time_stamp[philo_id] = data->current_clock;
	put_regular_status(data, philo_id, LEN_IS_THINKING, MESSAGE_THINKING);
	return (finished_meal_state);
}
