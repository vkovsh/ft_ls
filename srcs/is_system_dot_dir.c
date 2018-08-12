#include "ft_ls.h"

bool		is_system_dot_dir(char *dirname)
{
	char	*buf;

	buf = NULL;
	if ((buf = ft_strrchr(dirname, '/')) == NULL)
		buf = dirname;
	else
		buf += 1;
	if (!ft_strcmp(".", buf) || !ft_strcmp("..", buf))
		return (true);
	return (false);
}