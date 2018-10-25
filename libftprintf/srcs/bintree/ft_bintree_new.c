#include "libft.h"

t_bintree		*ft_bintree_new(const void *content,
				size_t content_size)
{
	t_bintree	*bintree;

	if (!(bintree = (t_bintree *)malloc(sizeof(bintree))))
		return (NULL);
	if (!(bintree->content = malloc(content_size)))
		return (NULL);
	memmove(bintree->content, content, content_size);
	bintree->left = NULL;
	bintree->right = NULL;
	return (bintree);
}