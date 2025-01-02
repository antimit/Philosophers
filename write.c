#include "philo.h"


#include "philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"RESET" %d has taken the 1° fork 🍴 (%d)\n", elapsed, philo->id, philo->first_fork->fork_id);
    else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"RESET" %d has taken the 2° fork 🍴 (%d)\n", elapsed, philo->id, philo->second_fork->fork_id);
    else if (EATING == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"RESET" %d is eating 🍝 (%ld)\n", elapsed, philo->id, philo->meals_counter);
    else if (SLEEPING == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"RESET" %d is sleeping 💤\n", elapsed, philo->id);
    else if (THINKING == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"RESET" %d is thinking 🤔\n", elapsed, philo->id);
    else if (DIED == status)
        printf(RED"\t%6ld %d died 💀💀💀\n"RESET, elapsed, philo->id);
}

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long elapsed = gettime(MILLISECOND);

    safe_mutex_handle(&philo->table->write_status, LOCK);

    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) && !simulation_finished(philo->table))
            printf(WHITE "%-6ld" RESET "%d has taken a fork\n", elapsed, philo->id);
        else if (EATING == status && !simulation_finished(philo->table))
            printf(WHITE "%-6ld" RESET "%d is eating\n", elapsed, philo->id);
        else if (SLEEPING == status && !simulation_finished(philo->table))
            printf(WHITE "%-6ld" RESET "%d is sleeping\n", elapsed, philo->id);
        else if (THINKING == status && !simulation_finished(philo->table))
            printf(WHITE "%-6ld" RESET "%d is thinking\n", elapsed, philo->id);
        else if (DIED == status)
            printf(WHITE "%-6ld" RESET "%d died\n", elapsed, philo->id);
    }

    safe_mutex_handle(&philo->table->write_status, UNLOCK);
}

