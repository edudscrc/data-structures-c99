#ifndef EDS_DYNAMIC_ARRAY_H
#define EDS_DYNAMIC_ARRAY_H

#include <stddef.h>

enum EdsResult { 
    EDS_SUCCESS = 0, 
    EDS_FAIL = 1, 
};

struct EdsError {
    int code;
    const char *message;
};

struct EdsArray;

struct EdsArray *EdsArray_new(size_t initial_capacity);

enum EdsResult EdsArray_append(struct EdsArray *arr, int value);
enum EdsResult EdsArray_insert(struct EdsArray *arr, size_t index, int value);

enum EdsResult EdsArray_pop(struct EdsArray *arr, int *removed_value);
enum EdsResult EdsArray_remove(struct EdsArray *arr, int value, int *removed_value);
enum EdsResult EdsArray_remove_at(struct EdsArray *arr, size_t index, int *removed_value);

enum EdsResult EdsArray_free(struct EdsArray *arr);

enum EdsResult EdsArray_clear(struct EdsArray *arr);

enum EdsResult EdsArray_get(const struct EdsArray *arr, size_t index, int *value);
enum EdsResult EdsArray_set(struct EdsArray *arr, size_t index, int value, int *old_value);

enum EdsResult EdsArray_size(const struct EdsArray *arr, size_t *result);
enum EdsResult EdsArray_capacity(const struct EdsArray *arr, size_t *result);

#endif // EDS_DYNAMIC_ARRAY_H
