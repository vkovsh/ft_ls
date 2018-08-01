#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_ftls	ftls;

	ft_bzero(&ftls, sizeof(t_ftls));
	get_args(argc, argv, &ftls);
	ftls.print_arg = (is_flag_set(ftls.flags, LS_SMALL_L)) ? print_verbose_info : print_info;
	parse_args(&ftls, ftls.arguments);
	return (0);
}