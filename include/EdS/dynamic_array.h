#ifndef EDS_DYNAMIC_ARRAY_H
#define EDS_DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define EDS_RETURN_SUCCESS 0
#define EDS_RETURN_ERROR -1

typedef struct EdS_darray_t {
    int *data;
    size_t size;
    size_t capacity;
} EdS_darray_t;

EdS_darray_t *EdS_darray_new(size_t initial_capacity);

int EdS_darray_append(EdS_darray_t *arr, int value);
int EdS_darray_insert(EdS_darray_t *arr, size_t index, int value);

int EdS_darray_pop(EdS_darray_t *arr, int *removed_value);
int EdS_darray_remove(EdS_darray_t *arr, int value, int *removed_value);
int EdS_darray_remove_at(EdS_darray_t *arr, size_t index, int *removed_value);

int EdS_darray_free(EdS_darray_t *arr);

int EdS_darray_clear(EdS_darray_t *arr);

int EdS_darray_get(const EdS_darray_t *arr, size_t index, int *value);
int EdS_darray_set(EdS_darray_t *arr, size_t index, int value, int *old_value);

int EdS_darray_print_info(EdS_darray_t *arr);
int EdS_darray_traverse(EdS_darray_t *arr);

#endif // EDS_DYNAMIC_ARRAY_H
