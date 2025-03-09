typedef struct pqueue pqueue;
struct pqueue {
	int k;
	void *data;
	pqueue *next;
	pqueue *prev;
};
//@param k - bigger first
void
qinsert(pqueue **phead, void *data, int k);

void
qlist(pqueue *head, void (*print_data)(void *));

void
qremove(pqueue **phead, int k);
