#include <sys/types.h>
#include <stdlib.h>

typedef struct			s_bintree
{
	void				*content;
	size_t				content_size;
	struct s_bintree	*left;
	struct s_bintree	*right;
}						t_bintree;

void					ft_bintree_add(t_bintree **t,
	t_bintree *node, int (*compare_keys)(void *, void *));

t_bintree				*ft_bintree_new(const void *content,
	size_t content_size);

t_bintree				*ft_bintree_find(t_bintree **t,
	void *key, int (*compare_keys)(void *, void *));

void					ft_bintree_delone(t_bintree **t,
	void (*del)(void *, size_t));

void					ft_bintree_del(t_bintree **t,
	void (*del)(void *, size_t));

void					ft_bintree_traverse(t_bintree *t);