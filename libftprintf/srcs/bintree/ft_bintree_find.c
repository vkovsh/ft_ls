#include "libft.h"

t_bintree		*ft_bintree_find(t_bintree **t,
				void *key,
				int (*compare_keys)(void *, void *))
{
	t_bintree	*find;
	int			i;

	find = *t;
	while (find)
		if (!(i = compare_keys(key, find->content)))
			return (find);
		else if (i < 0)
			find = find->left;
		else
			find = find->right;
	return (NULL);
}