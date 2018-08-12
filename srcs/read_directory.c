#include "ft_ls.h"

static inline bool	append_it(int flags, const char *name)
{
	return (name[0] != '.' ||
		is_flag_set(flags, LS_SMALL_A));
}

t_list				*read_directory(const char *dirname,
					t_ftls *ftls)
{
	DIR				*pdir;
	t_dirent		*pdirent;
	t_list			*dir_args;

	dir_args = NULL;
	if ((pdir = opendir(dirname)) == NULL)
		return (dir_args);
	while ((pdirent = readdir(pdir)) != NULL)
		if (append_it(ftls->flags, pdirent->d_name))
			set_catalog_from_arg(&dir_args,
				ft_strjoin_free(ft_strjoin(dirname, "/"),
				pdirent->d_name, TRUE, FALSE));
	closedir (pdir);
	return (dir_args);
}