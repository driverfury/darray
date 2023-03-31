# Dynamic Arrays in C

## Usage

```c
/* either initialize it to NULL or call da_create(arr) */
int *arr = NULL;

da_len(arr); /* == 0 */

da_push(arr, 88);   /* [ 88           ] */
da_push(arr, 32);   /* [ 88, 32       ] */
da_push(arr, 5567); /* [ 88, 32, 5567 ] */

da_len(arr); /* == 3 */

da_pop(arr);        /* [ 88, 32       ] */
da_pop(arr);        /* [ 88           ] */
da_pop(arr);        /* [              ] */

da_len(arr); /* == 0 */

da_destroy(arr); /* free dynamically allocated memory for the array */
```

You can index elements like you do with "normal arrays": ```arr[i]```.

## Example

Sum of all elements of the dynamic array

```c

#include <stdio.h>
#include "darray.h"

int sum(int *arr)
{
    int result;
    size_t len, i;

    len = da_len(arr);
    result = 0;

    for(i = 0; i < len; ++i)
    {
        result += arr[i];
    }

    return(result);
}

int main()
{
    int *arr;
    int result;

    da_create(arr);

    da_push(arr, 123);
    da_push(arr, 91);
    da_push(arr, 55);
    da_push(arr, 88);

    result = sum(arr);
    printf("Result: %d\n", result);

    da_destroy(arr);

    return(0);
}
```

## Advanced

You can use your own custom memory allocators by defining:

```c
/* Your custom allocator functions */
void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size);
void *my_free(void *ptr);

/* Overwrite this library's default memory functions */
#define da_malloc my_malloc
#define da_realloc my_realloc
#define da_free my_free
```
