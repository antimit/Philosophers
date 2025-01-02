#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //gettimeofday
# include <unistd.h>

// Define ANSI escape codes for bold text colors
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

# define DEBUG_MODE 0

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

struct					s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long last_meal_time; // time passed from last meal
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_table				*table;
};

struct					s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				all_threads_ready;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		write_status;
};

// utils
void					error_exit(const char *error);
long					gettime(t_time_code time_code);
void					precise_usleep(long usec, t_table *table);

// Parsing
void					parse_input(t_table *table, char **av);

// initialization
void					data_init(t_table *table);

// safe functions
void					*safe_malloc(size_t bytes);
void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

// synchro utils
void					wait_all_threads(t_table *table);

// Setters and getters
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					simulation_finished(t_table *table);

// Write
void					write_status(t_philo_status status, t_philo *philo,
							bool debug);

// Dinner
void					dinner_start(t_table *table);

#endif