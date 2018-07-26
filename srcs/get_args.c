#include "ft_ls.h"

void			get_args(int ac, char **av, t_ftls *ftls)
{
	int			i;
	int			j;
	const char	*flags[LS_FLAG_TOTAL] = FLAGS_ARRAY;
	t_catalog	tmp;

	i = ac;
	while (--i >= 1)
	{
		j = -1;
		while (++j < LS_FLAG_TOTAL)
		{
			if (!ft_strcmp(flags[j], av[i]))
			{
				ftls->flags |= 1 << j;
				break ;
			}
		}
		if (j == LS_FLAG_TOTAL)
		{
			tmp.name = av[i];
			stat(av[i], &(tmp.catalog_info));
			lstat(av[i], &(tmp.link_info));
			ft_lstadd(&(ftls->arguments), ft_lstnew(&tmp, sizeof(t_catalog)));
		}
	}
}