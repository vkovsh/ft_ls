#include "ft_ls.h"

t_filetype		get_file_type(const char *path)
{
	t_filetype	result;
	struct stat	link_info;
	int			type_mask;
	const int	type_macro[FILE_TYPE_TOTAL] = TYPE_ID_MACRO;

	if (lstat(path, &link_info) < 0)
		return (ERR);
	else
	{
		type_mask = link_info.st_mode & S_IFMT;
		result = ERR;
		while (++result < FILE_TYPE_TOTAL)
		{
			if (type_mask == type_macro[result])
				return (result);
		}
	}
	return (ERR);
}