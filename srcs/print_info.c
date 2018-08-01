#include "ft_ls.h"

void					print_info(t_catalog *catalog)
{
	const t_colorpair	cp[FILE_TYPE_TOTAL] = COLOR_PAIRS;
	t_colorpair			tmp;

	tmp = cp[catalog->filetype];
	ft_printf("%[*]{*}s ", tmp.bc, tmp.fc, catalog->name);
}