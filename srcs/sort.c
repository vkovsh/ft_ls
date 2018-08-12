#include "ft_ls.h"

void			swap(t_list *a, t_list *b)
{
	void		*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void			bubblesort(t_list **args,
					void *compare,
					void *compare_operator)
{
	t_list		*tmp;
	int			swap_count;
	int			general_swap = 0;

	swap_count = 1;
	while (swap_count != 0)
	{
		swap_count = 0;
		tmp = *args;
		while (tmp->next)
		{
			if (((comproute_t)compare)(tmp, tmp->next, compare_operator))
			{
				swap_count++;
				swap(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
		general_swap += swap_count;
	}
}