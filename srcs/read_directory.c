#include "ft_ls.h"

t_list				*read_directory(const char *dirname,
					t_ftls *ftls)
{
	DIR				*pdir;
	struct dirent	*pdirent;
	t_list			*dir_args;
	t_catalog		buf;

	dir_args = NULL;
	if ((pdir = opendir(dirname)) == NULL)
		return (dir_args);
	while ((pdirent = readdir(pdir)) != NULL)
	{
		if (pdirent->d_name[0] != '.' ||
			is_flag_set(ftls->flags, LS_SMALL_A))
		{
			buf.name = ft_strjoin(ft_strjoin(dirname, "/"), pdirent->d_name);
			buf.filetype = get_file_type(buf.name);
			ft_lstadd(&dir_args, ft_lstnew(&buf, sizeof(t_catalog)));
		}
	}
	closedir (pdir);
	return (dir_args);
}