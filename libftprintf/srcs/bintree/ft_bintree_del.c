#include "libft.h"

void	ft_bintree_del(t_bintree **t,
		void (*del)(void *, size_t))
{
	if ((*t)->left)
		ft_bintree_del(&((*t)->left), del);
	if ((*t)->right)
		ft_bintree_del(&((*t)->right), del);
	ft_bintree_delone(t, del);
}