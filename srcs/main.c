#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_ftls	ftls;

	ft_bzero(&ftls, sizeof(t_ftls));
	get_args(argc, argv, &ftls);
	ftls.print_arg = (is_flag_set(ftls.flags, LS_SMALL_L)) ? print_verbose_info : print_info;
	if (is_flag_set(ftls.flags, LS_ONE) ||
		is_flag_set(ftls.flags, LS_SMALL_L))
		ftls.delimiter = '\n';
	else
		ftls.delimiter = ' ';
	if (is_flag_set(ftls.flags, LS_BIG_U))
	{
		ftls.compare = NULL;
		ftls.compare_operator = NULL;
	}
	else if (is_flag_set(ftls.flags, LS_SMALL_T))
	{
		ftls.compare = compare_by_mod_date;
		if (is_flag_set(ftls.flags, LS_SMALL_R))
			ftls.compare_operator = operator_bigger;
		else
			ftls.compare_operator = operator_lesser;
	}
	else
	{
		ftls.compare = compare_case_insensitive;
		if (is_flag_set(ftls.flags, LS_SMALL_R))
			ftls.compare_operator = operator_lesser;
		else
			ftls.compare_operator = operator_bigger;
	}
	parse_args(&ftls, ftls.arguments, 0);
	return (0);
}