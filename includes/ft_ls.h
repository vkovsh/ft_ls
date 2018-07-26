#ifndef FTLS_H
# define FTLS_H
# include "ft_printf.h"
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
# define LS_SMALL_L 1
# define LS_BIG_R 2
# define LS_SMALL_A 4
# define LS_SMALL_R 8
# define LS_SMALL_D 16
# define FLAGS_ARRAY {"-l", "-R", "-a", "-r", "-d"}

typedef enum	s_lsflag
{
	LS_SMALL_L_POS,
	LS_BIG_R_POS,
	LS_SMALL_A_POS,
	LS_SMALL_R_POS,
	LS_SMALL_D_POS,
	LS_FLAG_TOTAL
}				t_lsflag;

typedef struct	s_catalog
{
	const char	*name; 
	struct stat	catalog_info;
	struct stat	link_info;
	t_list		*catalog_content;
}				t_catalog;

typedef struct	s_ftls
{
	int			flags;
	t_list		*arguments;
}				t_ftls;

void	get_args(int ac, char **av, t_ftls *ftls);
void	read_args(t_ftls *ftls);
void	print_verbose_info(t_catalog *catalog);

#endif