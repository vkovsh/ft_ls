#include "ft_ls.h"

void				read_directory(const char *dirname,
					t_ftls *ftls)
{
	DIR				*pdir;
	struct dirent	*pdirent;

	pdir = opendir(dirname);
	if (pdir == NULL)
		ft_printf ("Cannot open directory '%s'\n", dirname);
	while ((pdirent = readdir(pdir)) != NULL)
	{
		if (pdirent->d_name[0] != '.' ||
			is_flag_set(ftls->flags, LS_SMALL_A))
			ft_printf("%s ", pdirent->d_name);
	}
	ft_printf("\n\n");
	closedir (pdir);
}

void				parse_args(t_ftls *ftls, t_list *args)
{
	t_catalog		*catalog;

	while (args)
	{
		catalog = (t_catalog *)(args->content);
		if (catalog->filetype == DIR_FILE)
			ftls->print_arg(catalog);
		else
			ftls->print_arg(catalog);
		ft_printf("\n");
		args = args->next;
	}
}