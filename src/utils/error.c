# include "../../includes/minirt.h"

// Error reporting function
void error_exit(char *message)
{
	ft_putstr_fd(ERROR_MESSAGE, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	// clean up function
	exit(1);
}
