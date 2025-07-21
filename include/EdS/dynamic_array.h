#ifndef EDS_DYNAMIC_ARRAY_H
#define EDS_DYNAMIC_ARRAY_H

#include <stddef.h>

enum EdsResult { 
    EDS_SUCCESS = 0, 
    EDS_ELEMENT_NOT_FOUND = 1,
    EDS_ERROR_MALLOC_FAILED = -1, 
    EDS_ERROR_REALLOC_FAILED = -2,
    EDS_ERROR_INVALID_PARAMETER = -3,    // Example: passing 0 as initial capacity to Dynamic Array
    EDS_ERROR_NULL_POINTER_PASSED = -4,  // Example: passing NULL to a pointer parameter
    EDS_ERROR_INDEX_OUT_OF_BOUNDS = -5,
    EDS_ERROR_ARITHMETIC_OVERFLOW = -6,
};

struct EdsArray;

enum EdsResult EdsArray_new(struct EdsArray **arr, size_t initial_capacity);

enum EdsResult EdsArray_append(struct EdsArray *arr, int value);
enum EdsResult EdsArray_insert(struct EdsArray *arr, size_t index, int value);

enum EdsResult EdsArray_pop(struct EdsArray *arr, int *removed_value);
enum EdsResult EdsArray_remove(struct EdsArray *arr, int value, int *removed_value);
enum EdsResult EdsArray_remove_at(struct EdsArray *arr, size_t index, int *removed_value);

enum EdsResult EdsArray_free(struct EdsArray *arr);

enum EdsResult EdsArray_clear(struct EdsArray *arr);

enum EdsResult EdsArray_get(const struct EdsArray *arr, size_t index, int *value);
enum EdsResult EdsArray_set(struct EdsArray *arr, size_t index, int value, int *old_value);

enum EdsResult EdsArray_find(const struct EdsArray *arr, int value);

enum EdsResult EdsArray_size(const struct EdsArray *arr, size_t *result);
enum EdsResult EdsArray_capacity(const struct EdsArray *arr, size_t *result);

#endif // EDS_DYNAMIC_ARRAY_H
