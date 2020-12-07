#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define	GET		NULL
#define	UNSET	-1
#define	SUCCESS	1
#define	FAILURE	-1
#define	USAGE0	"Philo: Usage: positive value only\n"
#define	USAGE1	"number_of_philosopher time_to_die time_to_eat time_to_sleep\n"
#define	USAGE2	"[number_of_time_each_philosophers_must_eat]\n"

#define	NB_OF_USEC_ARGS	3

enum	e_times_arguments
{
	T_TO_DIE,
	T_TO_EAT,
	T_TO_SLEEP
};

#define	BLACK 	"\033[0;30m"
#define	RED 	"\033[0;31m"
#define	GREEN 	"\033[0;32m"
#define	YELLOW 	"\033[0;33m"
#define	BLUE 	"\033[0;34m"
#define	PURPLE 	"\033[0;35m"
#define	CYAN 	"\033[0;36m"
#define	WHITE 	"\033[0;37m"
#define	RESET 	"\033[0m"

typedef struct	s_data
{
	// pthread_mutex_t	mutex;
	int				nb_philo;
	unsigned int	usec[NB_OF_USEC_ARGS];
	int				nb_eat_turns;
}				t_data;

/*
**	UTILS
*/

t_data			*get_data(t_data *mem);

/*
**	ARGUMENTS
*/

void			put_usage(void);
int				check_arguments(const int ac, const char **av);
int				process_arguments(t_data *data, const char **av);

