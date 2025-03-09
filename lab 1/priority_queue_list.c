#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include "priority_queue_list.h"

void
qlist(pqueue *head, void (*print_data)(void *)) {
	pqueue *p;
	
	for (p = head; p != NULL; p = p->next) {
		printf("%d: ", p->k);
		print_data(p->data);
		printf("\n");
	}
	
}

void
qinsert(pqueue **phead, void *data, int k) {
	
	struct pqueue* p;
	p = (*phead); /* wez adres analizowanego elementu */
	if (p != NULL) /* czy pocz¹tek listy */
	{
		if (k <= (p->k)) /* czy gorszy priorytet */
		{
			if (p->next == NULL) /* koniec listy */
			{ /* utworz nowy element */
				p->next = (struct pqueue*)malloc(sizeof(struct pqueue));
				/* zainicjuj skladowe nowego elementu */
				p->next->k = k;
				p->next->data = data;
				p->next->next = NULL;
				p->next->prev = p;
			}
			else
				qinsert(&p->next, data, k);
		}
		else
		{
			struct pqueue* p_prev = p->prev;
			/* utworz nowy element */
			p->prev = (struct pqueue*)malloc(sizeof(struct pqueue));
			/* zapamietaj adres nowego elementu */
			p = p->prev;
			/* zainicjuj skladowe nowego elementu */
			p->k = k;
			p->data = data;
			p->next = *phead;
			p->prev = p_prev;
			if (p_prev != NULL)
				p_prev->next = p;
			*phead = p;
		}
	}
	else /* nowa lista*/
	{ /* utworz nowy element */
		p = (struct pqueue*)malloc(sizeof(struct pqueue));
		/* zainicjuj skladowe nowego elementu */
		p->k = k;
		p->data = data;
		p->next = NULL;
		p->prev = NULL;
		*phead = p; /* zapisz nowy element jako g³owê nowej listy */
	}
}


void
qremove(pqueue **phead, int k) {
	if (*phead != NULL)
	{
		struct pqueue* p;
		p = (*phead);
		if (p->k == k)
		{
			if (p->prev != NULL)
			{
				p->prev->next = p->next;
			}
			else
			{
				*phead = p->next;
			}
			if (p->next != NULL)
			{
				p->next->prev = p->prev;
			}
			qremove(&(p->next), k);
			free(p);
		}
		else if (p->k > k)
		{
				qremove(&(p->next), k);
		}
	}
}

