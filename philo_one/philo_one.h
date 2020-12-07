#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

# define	BLACK 	"\033[0;30m"
# define	RED 	"\033[0;31m"
# define	GREEN 	"\033[0;32m"
# define	YELLOW 	"\033[0;33m"
# define	BLUE 	"\033[0;34m"
# define	PURPLE 	"\033[0;35m"
# define	CYAN 	"\033[0;36m"
# define	WHITE 	"\033[0;37m"
# define	RESET 	"\033[0m"

# define	GET		NULL

# define	UNSET	-1
# define	SUCCESS	1
# define	FAILURE	-1

# define	USAGE0	"Philo: Usage: positive value only\n"
# define	USAGE1	"number_of_philosopher time_to_die "
# define	USAGE2	"time_to_eat time_to_sleep\n"
# define	USAGE3	"[number_of_time_each_philosophers_must_eat]\n"

# define	ERR_MALLOC	"Philo: error: malloc() failed\n"

# define	NB_OF_USEC_ARGS	5

# define	MESSAGE_HAS_TAKEN_FORK	RED" has taken a fork\n"RESET
# define	MESSAGE_IS_EATING		GREEN" is eating\n"RESET
# define	MESSAGE_IS_SLEEPING		BLUE" is sleeping\n"RESET
# define	MESSAGE_IS_THINKING		YELLOW" is thinking\n"RESET
# define	MESSAGE_IS_DEAD			PURPLE" died\n"RESET

enum	e_times_arguments
{
	NB_PHILO,
	T_TO_DIE,
	T_TO_EAT,
	T_TO_SLEEP,
	NB_MEALS
};

typedef enum	e_state
{
	sleeping_state,
	eating_state,
	thinking_state,
	dead_state,
	startup_state
}				t_state;

typedef struct	s_data
{
	// pthread_mutex_t	mutex;
	// pthread_mutex_t	stdout_mutex;
	int				nb_dead_philo;
	int				param[NB_OF_USEC_ARGS];
	unsigned int	*last_meal;
	unsigned int	*nb_meals_eaten;
}				t_data;

/*
**	MAIN_PROCESS
*/

void process_philo(t_data *data);

/*
**	UTILS
*/

t_data			*get_data(t_data *mem);
void			ft_put_str_fd(int fd, const char *s);
void			ft_putnbr(unsigned int n);

/*
**	ARGUMENTS
*/

void			put_usage(void);
int				check_arguments(const int ac, const char **av);
int				process_arguments(t_data *data, const char **av);

#endif
