#include "ft_ls.h"

void					print_info(t_catalog *catalog)
{
	const t_colorpair	cp[FILE_TYPE_TOTAL] = COLOR_PAIRS;
	t_colorpair			tmp;
	char				*name;

	name = ft_strrchr(catalog->name, '/');
	name = (name) ? name + 1 : (char *)(catalog->name);
	tmp = cp[catalog->filetype];
	ft_printf("%[*]{*}s", tmp.bc, tmp.fc, name);
}