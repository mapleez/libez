#ifndef __QUEUE_H_
#	define __QUEUE_H_
#include <stdbool.h>

#	define _element   int
#	define _element_size    (sizeof (_element))
struct _ez_queue {
	int capacity;
	int front;
	int real;
	_element* array;
};

typedef struct _ez_queue* _queue;
#	define _queue_size		(sizeof (struct _ez_queue))

extern bool full_queue (_queue);
extern bool empty_queue (_queue);
extern _queue create_queue (int);
extern void dispose_queue (_queue);
extern bool enqueue (_queue, _element);
extern bool dequeue (_queue);
extern _element* front (_queue);
extern _element* frontanddequeue (_queue);

#endif // ~ __QUEUE_H_
