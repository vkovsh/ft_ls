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
# define FLAGS_ARRAY "lRard"
# define PERM_FULL "-rwxrwxrwx"
# define PERM_EMPTY "----------"
# define HELP_TXT "Try './ft_ls --help' for more information.\n"
# define PERM_MACRO {0, S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH}
# define DIR_COLOR 0x0000ff
# define SOFT_LINK_COLOR 0x00ffff
# define BIN_COLOR 0x00ff00
# define REG_COLOR 0xffffff
# define FIF_COLOR 0x0f00f0
# define TYPE_ID_MACRO {S_IFREG, S_IFDIR, S_IFCHR, S_IFBLK, S_IFIFO, S_IFLNK, S_IFSOCK}
# define REG_PAIR (t_colorpair){.fc = 0xffffff}
# define DIR_PAIR (t_colorpair){.fc = 0x0000ff}
# define CHR_PAIR (t_colorpair){.fc = 0xa0a000, .bc = 0xff0000}
# define BLK_PAIR (t_colorpair){.fc = 0xa0a000, .bc = 0xff0000}
# define FIFO_PAIR (t_colorpair){.fc = 0xa0a000}
# define LNK_PAIR (t_colorpair){.fc = 0x00ffff}
# define SOC_PAIR (t_colorpair){.fc = 0x00ffff}
# define COLOR_PAIRS {REG_PAIR, DIR_PAIR, CHR_PAIR, BLK_PAIR, FIFO_PAIR, LNK_PAIR, SOC_PAIR}

typedef struct	s_colorpair
{
	int			fc;
	int			bc;
}				t_colorpair;

typedef enum	e_perm
{
	IRUSR,
	IWUSR,
	IXUSR,
	IRGRP,
	IWGRP,
	IXGRP,
	IROTH,
	IWOTH,
	IXOTH,
	PERM_TOTAL
}				t_perm;

typedef enum	e_filetype
{
	ERR = -1,
	REG_FILE,
	DIR_FILE,
	CHR_FILE,
	BLK_FILE,
	FIFO_FILE,
	LNK_FILE,
	SOCK_FILE,
	FILE_TYPE_TOTAL
}				t_filetype;

typedef enum	e_lsflag
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
	t_filetype	filetype;
}				t_catalog;

typedef struct	s_ftls
{
	int			flags;
	t_list		*arguments;
	void		(*print_arg)(t_catalog *catalog);
}				t_ftls;

void		get_args(int ac, char **av, t_ftls *ftls);
void		parse_args(t_ftls *ftls, t_list *arguments);
void		print_verbose_info(t_catalog *catalog);
void		print_info(t_catalog *catalog);
bool		is_flag_set(int flags, int flag);
t_filetype	get_file_type(const char *path);

#endif