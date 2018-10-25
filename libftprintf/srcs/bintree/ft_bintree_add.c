#include "libft.h"

void	ft_bintree_add(t_bintree **t,
		t_bintree *node,
		int (*compare_keys)(void *, void *))
{
	if (*t == NULL)
		*t = node;
	else
	{
		if (compare_keys(node->content, (*t)->content) < 0)
		{
			if ((*t)->left)
				ft_bintree_add(&((*t)->left), node, compare_keys);
			else
				(*t)->left = node;
		}
		else
		{
			if ((*t)->right)
				ft_bintree_add(&((*t)->right), node, compare_keys);
			else
				(*t)->right = node;
		}
	}
}