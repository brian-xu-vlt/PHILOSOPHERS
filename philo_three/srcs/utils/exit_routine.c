/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:20:41 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 17:20:42 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_free(void *mem)
{
	if (mem != NULL)
	{
		free(mem);
		mem = NULL;
	}
}

void	exit_routine_childprocess(t_code_err err)
{
	t_data				*data;
	static const char	*message[NB_ERR_CODE] =
	{ ERR_MALLOC, ERR_FORK, ERR_SEM, ERR_PTHREAD };

	data = get_data(GET);
	if (data != NULL)
	{
		safe_sem_close(data->sem_race_starter, SEM_NAME_RACE_STARTER);
		safe_sem_close(data->sem_stdout, SEM_NAME_STDOUT);
		safe_sem_close(data->sem_forks_heap, SEM_NAME_FORKS_HEAP);
	}
	if (err < NB_ERR_CODE)
		ft_put_str_fd(STDERR_FILENO, message[err]);
	exit(CHILD_FAILURE);
}

void	exit_routine_mainprocess(t_code_err err, t_gdata *gdata)
{
	static const char	*message[NB_ERR_CODE] =
	{ ERR_MALLOC, ERR_FORK, ERR_SEM, ERR_PTHREAD };

	if (gdata != NULL)
	{
		destroy_sem(gdata);
		safe_free(gdata->philo_pids);
	}
	if (err < NB_ERR_CODE)
		ft_put_str_fd(STDERR_FILENO, message[err]);
	exit(FAILURE_RETURN);
}
