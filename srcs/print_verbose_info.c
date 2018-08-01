#include "ft_ls.h"

void            get_permission_str(struct stat *s,
                char *perm, int *const name_color)
{
	const int	pm[10] = PERM_MACRO;
	t_perm		i;
	bool		is_bin;
	
	perm[10] = '\0';
	is_bin = (s->st_mode & S_IXUSR) |
            (s->st_mode & S_IXGRP) |
            (s->st_mode & S_IXOTH);
    if (S_ISDIR(s->st_mode))
    {
        *name_color = DIR_COLOR;
        perm[0] = 'd';
    }
    else if (S_ISLNK(s->st_mode))
    {
        *name_color = SOFT_LINK_COLOR;
        perm[0] = 'l';
    }
    else if (is_bin == true)
        *name_color = BIN_COLOR;
    else
    {
        *name_color = REG_COLOR;
        perm[0] = '-';
    }
    i = 0;
    while (++i <= PERM_TOTAL)
        perm[i] = (s->st_mode & pm[i]) ? PERM_FULL[i] : '-';
}

void				print_from_stat(struct stat *s,
					const char *cname,
					const char *tname,
                    t_colorpair pair)
{
	char			perm[11];
	int				name_color;
    struct passwd	*pw;
    struct group  	*gr;
	char			*date;
    
	date = ctime(&s->st_mtime);
	pw = getpwuid(s->st_uid);
	gr = getgrgid(s->st_gid);
    get_permission_str(s, perm, &name_color);
    ft_printf("%-11s%d %s %s %d %.12s %[*]{*}s",
			perm,
			s->st_nlink,
			pw->pw_name,
			gr->gr_name,
			s->st_size,
			&date[4],
			pair.bc,
            pair.fc,
			cname);
    if (tname)
        ft_printf(" -> %s\n", tname);
	else
		ft_printf("\n");
}

void			print_verbose_info(t_catalog *catalog)
{
	struct stat	cstat;
    struct stat linkstat;
	const char	*cname;
    char  target_name[256];
    const t_colorpair   cp[FILE_TYPE_TOTAL] = COLOR_PAIRS;

	cname = catalog->name;
    stat(cname, &cstat);
	lstat(cname, &linkstat);
    ft_bzero(target_name, 256);
    readlink(cname, target_name, 256);
    if (S_ISLNK(linkstat.st_mode))
        print_from_stat(&linkstat, cname, target_name, cp[catalog->filetype]);
    else
        print_from_stat(&cstat, cname, NULL, cp[catalog->filetype]);
}