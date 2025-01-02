#include "philo.h"

int	main(int ac, char **av)
{
	t_table table;
	if (5 == ac || 6 == ac)
	{
        parse_input(&table, av);
        data_init(&table);
        dinner_start(&table);
        clean(&table);
	}
	else
	{
		error_exit("Wrong input:\n" GREEN"Correct is ./philo 5 800 200 200[5]"RESET);
	}
}