/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_verbose_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 13:52:56 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/14 13:52:58 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool					is_binary(t_stat *s)
{
	return ((s->st_mode & S_IXUSR) |
			(s->st_mode & S_IXGRP) |
			(s->st_mode & S_IXOTH));
}

void					get_permission_str(
						t_catalog *c,
						char *perm)
{
	const int			pm[10] = PERM_MACRO;
	t_perm				i;

	perm[10] = '\0';
	perm[0] = FILE_TYPE_MARKERS[c->filetype];
	i = 0;
	while (++i <= PERM_TOTAL)
		perm[i] = (c->clstat.st_mode & pm[i]) ?
			PERM_FULL[i] : '-';
}

const char				*cut_name(const char *name)
{
	char				*result;

	result = ft_strrchr(name, '/');
	return ((result) ? result + 1 : name);
}

void					print_from_stat(t_catalog *c,
						const char *tname,
						t_colorpair pair)
{
	char				perm[11];
	struct passwd		*pw;
	struct group		*gr;
	char				*date;

	date = ctime(&c->clstat.st_mtime);
	pw = getpwuid(c->clstat.st_uid);
	gr = getgrgid(c->clstat.st_gid);
	get_permission_str(c, perm);
	ft_printf("%-11s%d %s %s %d %.12s %[*]{*}s",
			perm,
			c->clstat.st_nlink,
			pw->pw_name,
			gr->gr_name,
			c->clstat.st_size,
			&date[4],
			pair.bc,
			pair.fc,
			cut_name(c->name));
	if (tname)
		ft_printf(" -> %s", tname);
}

void					print_verbose_info(t_catalog *catalog,
						char delim)
{
	const char			*cname;
	char				target_name[NAME_MAX + 1];
	const t_colorpair	cp[FILE_TYPE_TOTAL] = COLOR_PAIRS;

	cname = catalog->name;
	if (catalog->filetype == LNK_FILE)
	{
		ft_bzero(target_name, NAME_MAX + 1);
		readlink(cname, target_name, NAME_MAX + 1);
		if (catalog->stat_res < 0)
			print_from_stat(catalog, target_name,
			(t_colorpair){.fc = 0xff0000});
		else
			print_from_stat(catalog, target_name,
			cp[catalog->filetype]);
	}
	else
	{
		if (catalog->filetype == REG_FILE &&
			is_binary(&(catalog->clstat)))
		{
			print_from_stat(catalog, NULL,
				(t_colorpair){.fc = 0xff0000});
		}
		else
			print_from_stat(catalog, NULL,
				cp[catalog->filetype]);
	}
	ft_putchar(delim);
}
