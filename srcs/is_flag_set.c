#include "ft_ls.h"

bool		is_flag_set(int flags, int flag)
{
	bool	is_set;

	is_set = flags & flag;
	return (is_set);
}