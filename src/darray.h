#ifndef DARRAY_H
#define DARRAY_H

#ifndef da_malloc
#include <stdlib.h>
#define da_malloc malloc
#define da_realloc realloc
#define da_free free
#endif

#include <stddef.h>

typedef struct
darray
{
    size_t cap;
    size_t len;
} darray;

#define da_hdr_(a) ((darray*)(a)-1)
#define da_len_(a) ((a)?((da_hdr_(a))->len):0)
#define da_cap_(a) ((a)?((da_hdr_(a))->cap):0)
#define da_dat_(da) ((void*)((da) + 1))

#define DARRAY_STARTING_LEN 10

void*
da_create_(size_t item_size)
{
    darray *da = da_malloc(sizeof(darray) + item_size*DARRAY_STARTING_LEN);
    da->cap = DARRAY_STARTING_LEN;
    da->len = 0;
    return(da_dat_(da));
}

void
da_destroy_(void *a)
{
    if(!a)
    {
        return;
    }

    da_free((void *)da_hdr_(a));
}

void*
da_grow_(void *a, size_t item_size)
{
    size_t new_cap;
    size_t new_tot_size;
    darray *new_da;

    new_cap = da_cap_(a)*2 + 1;
    new_tot_size = sizeof(darray) + new_cap*item_size;

    new_da = da_realloc(da_hdr_(a), new_tot_size);
    if(!new_da)
    {
        return(0);
    }

    new_da->cap = new_cap;

    return(da_dat_(new_da));
}

#define da_create(a) ((a)=da_create_(sizeof(*(a))))
#define da_len(a) da_len_(a)
#define da_push(a, item)\
    do\
    {\
        if(!(a)) (a) = da_create_(sizeof(*(a)));\
        if(da_cap_(a) < da_len_(a) + 1) (a) = da_grow_((a),sizeof(*(a)));\
        (a)[da_hdr_(a)->len++] = (item);\
    } while(0)
#define da_pop(a)\
    do\
    {\
        if((a) != 0 && da_len_(a) > 0)\
        {\
            da_hdr_(a)->len -= 1;\
        }\
    } while(0)
#define da_destroy(a) da_destroy_(a)

#undef DARRAY_STARTING_LEN

#endif
