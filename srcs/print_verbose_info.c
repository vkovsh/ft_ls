#include "ft_ls.h"

void            get_permission_str(struct stat *s,
                char *perm, int *const name_color)
{
    perm[10] = '\0';
    if (S_ISDIR(s->st_mode))
    {
        *name_color = 0x0000ff;
        perm[0] = 'd';
    }
    else if (S_ISLNK(s->st_mode))
    {
        *name_color = 0x00ffff;
        perm[0] = 'l';
    }
    else if ((s->st_mode & S_IXUSR) ||
            (s->st_mode & S_IXGRP) ||
            (s->st_mode & S_IXOTH))
    {
        *name_color = 0x00ff00;
    }
    else
    {
        *name_color = 0xffffff;
        perm[0] = '-';
    }
    perm[1] = (s->st_mode & S_IRUSR) ? 'r' : '-';
    perm[2] = (s->st_mode & S_IWUSR) ? 'w' : '-';
    perm[3] = (s->st_mode & S_IXUSR) ? 'x' : '-';
    perm[4] = (s->st_mode & S_IRGRP) ? 'r' : '-';
    perm[5] = (s->st_mode & S_IWGRP) ? 'w' : '-';
    perm[6] = (s->st_mode & S_IXGRP) ? 'x' : '-';
    perm[7] = (s->st_mode & S_IROTH) ? 'r' : '-';
    perm[8] = (s->st_mode & S_IWOTH) ? 'w' : '-';
    perm[9] = (s->st_mode & S_IXOTH) ? 'x' : '-';
}

void            print_from_stat(struct stat *s,
                const char *cname, const char *tname)
{
    char        perm[11];
    int         name_color;
    
    get_permission_str(s, perm, &name_color);
    ft_printf("%-11s", perm);
    ft_printf("%d ", s->st_nlink);
    struct passwd *pw = getpwuid(s->st_uid);
    ft_printf("%s ", pw->pw_name);
    struct group  *gr = getgrgid(s->st_gid);
    ft_printf("%s ", gr->gr_name);
    ft_printf("%d ", s->st_size);
    char *date = ctime(&s->st_mtime);
    ft_printf("%.12s ", &date[4]);
    ft_printf("%{*}s", name_color, cname);
    if (tname)
        ft_printf(" -> %s", tname);
    ft_printf("\n");
}

void			print_verbose_info(t_catalog *catalog)
{
	struct stat	cstat;
    struct stat linkstat;
	const char	*cname;
    char  target_name[256];

	cstat = catalog->catalog_info;
	cname = catalog->name;
    linkstat = catalog->link_info;
    ft_bzero(target_name, 256);
    readlink(cname, target_name, 256);
    if (S_ISLNK(linkstat.st_mode))
        print_from_stat(&linkstat, cname, target_name);
    else
        print_from_stat(&cstat, cname, NULL);
}