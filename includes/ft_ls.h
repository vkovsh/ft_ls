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
# define LS_ONE 32
# define LS_BIG_U 64
# define LS_SMALL_T 128
# define FLAGS_ARRAY "lRard1Ut"
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
# define DIR_PAIR (t_colorpair){.fc = 0x6666FF}
# define CHR_PAIR (t_colorpair){.fc = 0xa0a000, .bc = 0xff0000}
# define BLK_PAIR (t_colorpair){.fc = 0xa0a000, .bc = 0xff0000}
# define FIFO_PAIR (t_colorpair){.fc = 0xa0a000}
# define LNK_PAIR (t_colorpair){.fc = 0x00ffff}
# define SOC_PAIR (t_colorpair){.fc = 0x00ffff}
# define COLOR_PAIRS {REG_PAIR, DIR_PAIR, CHR_PAIR, BLK_PAIR, FIFO_PAIR, LNK_PAIR, SOC_PAIR}
# define FILE_TYPE_MARKERS "-dcbpls"

typedef bool (*comproute_t)(t_list *, t_list *, void *);
typedef bool (*compoproute_t)(int, int);
typedef struct stat t_stat;
typedef struct dirent t_dirent;

typedef struct		s_colorpair
{
	int				fc;
	int				bc;
}					t_colorpair;

typedef enum		e_perm
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
}					t_perm;

typedef enum		e_filetype
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
}					t_filetype;

typedef enum		e_lsflag
{
	LS_SMALL_L_POS,
	LS_BIG_R_POS,
	LS_SMALL_A_POS,
	LS_SMALL_R_POS,
	LS_SMALL_D_POS,
	LS_ONE_POS,
	LS_BIG_U_POS,
	LS_SMALL_T_POS,
	LS_FLAG_TOTAL
}					t_lsflag;

typedef struct		s_catalog
{
	char			*name;
	t_filetype		filetype;
	t_stat			cstat;
	t_stat			clstat;
	int				stat_res;
	int				lstat_res;
}					t_catalog;

typedef struct		s_ftls
{
	int				flags;
	t_list			*arguments;
	char			delimiter;
	void			(*print_arg)(t_catalog *);
	comproute_t		compare;
	compoproute_t	compare_operator;
}					t_ftls;

void		set_catalog_from_arg(t_list **, char *);
bool		operator_bigger(int, int);
bool		operator_lesser(int, int);
bool		compare_case_insensitive(t_list *, t_list *, void *);
bool		compare_by_mod_date(t_list *, t_list *, void *);
bool		is_system_dot_dir(char *);
void		bubblesort(t_list **, void *, void *);
void		get_args(int, char **, t_ftls *);
void		parse_args(t_ftls *, t_list *, int);
void		print_verbose_info(t_catalog *);
void		print_info(t_catalog *);
bool		is_flag_set(int, int);
t_filetype	get_file_type(t_catalog *);
t_list		*read_directory(const char *, t_ftls *);

#endif