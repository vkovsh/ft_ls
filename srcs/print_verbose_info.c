#include "ft_ls.h"

bool			is_binary(struct stat *s)
{
	return ((s->st_mode & S_IXUSR) |
			(s->st_mode & S_IXGRP) |
			(s->st_mode & S_IXOTH));
}

void            get_permission_str(struct stat *s,
                char *perm)
{
	const int	pm[10] = PERM_MACRO;
	t_perm		i;
	
	perm[10] = '\0';
    if (S_ISDIR(s->st_mode))
        perm[0] = 'd';
    else if (S_ISLNK(s->st_mode))
        perm[0] = 'l';
    else
        perm[0] = '-';
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
    struct passwd	*pw;
    struct group  	*gr;
	char			*date;
    
	date = ctime(&s->st_mtime);
	pw = getpwuid(s->st_uid);
	gr = getgrgid(s->st_gid);
    get_permission_str(s, perm);
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
        ft_printf(" -> %s", tname);
}

void			print_verbose_info(t_catalog *catalog)
{
	struct stat	cstat;
    struct stat linkstat;
	const char	*cname;
    char  target_name[256];
    const t_colorpair   cp[FILE_TYPE_TOTAL] = COLOR_PAIRS;

	cname = catalog->name;
    if (catalog->filetype == LNK_FILE)
	{
		lstat(cname, &linkstat);
		ft_bzero(target_name, 256);
		readlink(cname, target_name, 256);
        print_from_stat(&linkstat, cname, target_name, cp[catalog->filetype]);
	}
	else
	{
		stat(cname, &cstat);
		print_from_stat(&cstat, cname, NULL, cp[catalog->filetype]);
	}
}