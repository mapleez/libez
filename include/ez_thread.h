#ifndef _EZ_THREAD_H_
#	define _EZ_THREAD_H_

extern void (* ez_mutex_create) (void **);
extern void (* ez_mutex_destroy) (void *);
extern void (* ez_mutex_lock) (volatile void *);
extern void (* ez_mutex_unlock) (volatile void *);

#	define MUTEX_DEFINE(id)         void *id##_mutex
#	define MUTEX_DEFINE_STATIC(id)  static void *id##_mutex
#	define MUTEX_CREATE(id)         ez_mutex_create (&id##_mutex)
#	define MUTEX_DESTROY(id)        ez_mutex_destroy (id##_mutex)
#	define MUTEX_LOCK(id)           ez_mutex_lock (id##_mutex)
#	define MUTEX_UNLOCK(id)         ez_mutex_unlock (id##_mutex)


#endif // _EZ_THREAD_H_

