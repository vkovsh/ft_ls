#include "ft_ls.h"

void				parse_args(t_ftls *ftls, t_list *args)
{
	t_catalog		*catalog;
	t_list			*dirs;
	char			delimiter;

	dirs = NULL;
	if (is_flag_set(ftls->flags, LS_ONE) ||
		is_flag_set(ftls->flags, LS_SMALL_L))
		delimiter = '\n';
	else
		delimiter = ' ';
	while (args)
	{
		catalog = (t_catalog *)(args->content);
		if (catalog->filetype == DIR_FILE)
			ft_lstadd(&dirs, ft_lstnew(catalog, sizeof(t_catalog)));
		else
		{
			ftls->print_arg(catalog);
			ft_putchar(delimiter);
		}
		args = args->next;
	}
	ft_printf("\n");
	while (dirs)
	{
		catalog = (t_catalog *)(dirs->content);
		ft_printf("\n%[*]{*}s:\n", 0x00ff00, 0x0000ff, catalog->name);
		parse_args(ftls, read_directory(catalog->name, ftls));
		dirs = dirs->next;
	}
}