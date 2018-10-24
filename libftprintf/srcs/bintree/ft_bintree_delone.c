#include "libft.h"

void	ft_bintree_delone(t_bintree **t,
		void (*del)(void *, size_t))
{
	del((*t)->content, (*t)->content_size);
	free(*t);
	*t = NULL;
}