#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_ftls	ftls;

	ft_bzero(&ftls, sizeof(t_ftls));
	get_args(argc, argv, &ftls);
	parse_args(&ftls);
	return (0);
}