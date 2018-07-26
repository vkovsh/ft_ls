#include "ft_ls.h"

int					is_directory(const char *path)
{
	struct stat		statbuf;
	
	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void				read_directory(const char *dirname)
{
	DIR				*pdir;
	struct dirent	*pdirent;

	pdir = opendir(dirname);
	if (pdir == NULL)
		ft_printf ("Cannot open directory '%s'\n", dirname);
	while ((pdirent = readdir(pdir)) != NULL)
	{
		ft_printf ("%s ", pdirent->d_name);
	}
	ft_printf("\n\n");
	closedir (pdir);
}

void				read_args(t_ftls *ftls)
{
	t_list			*argc;

	argc = ftls->arguments;
	while (argc)
	{
		if (is_directory(((t_catalog *)(argc->content))->name))
		{
			ft_printf("%s:\n", ((t_catalog *)(argc->content))->name);
			read_directory(((t_catalog *)(argc->content))->name);
		}
		else
			print_verbose_info((t_catalog *)(argc->content));
			//ft_printf("%s\n", ((t_catalog *)(argc->content))->name);
		argc = argc->next;
	}
}