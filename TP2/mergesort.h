#ifndef __MERGESORT_H__
#define __MERGESORT_H__
#include <stddef.h>

void mergesort(void** vector,int cantidad_elementos,int (*comparador)(void*, void*));

#endif /* __MERGESORT_H__ */