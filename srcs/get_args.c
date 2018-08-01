#include "ft_ls.h"

void			set_flags_from_arg(t_ftls *ftls, char *str)
{
	int			i;
	int			j;
	const char	flags[LS_FLAG_TOTAL] = FLAGS_ARRAY;

	i = 0;
	while (str[i])
	{
		j = -1;
		while(++j < LS_FLAG_TOTAL)
		{
			if (str[i] == flags[j])
				ftls->flags |= 1 << j;
			else if (!ft_isalnum(str[i]))
			{
				ft_printf("%s '%c'\n",
					"ft_ls: invalid option --", str[i]);
				ft_printf(HELP_TXT);
				exit(1);
			}
		}
		i++;
	}
}

void			set_catalog_from_arg(t_ftls *ftls, char *str)
{
	t_catalog	tmp;

	tmp.name = str;
	tmp.filetype = get_file_type(str);
	ft_lstadd(&(ftls->arguments),
		ft_lstnew(&tmp, sizeof(t_catalog)));
}

void			get_args(int ac, char **av, t_ftls *ftls)
{
	int			i;

	i = ac;
	while (--i >= 1)
		if (*(av[i]) == '-' && av[i][1])
			set_flags_from_arg(ftls, &(av[i][1]));
		else
			set_catalog_from_arg(ftls, av[i]);
	if (ftls->arguments == NULL)
		set_catalog_from_arg(ftls, ".");
}