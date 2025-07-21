#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/EdS/dynamic_array.h"

struct EdsArray {
    int *data;
    size_t capacity;
    size_t size;
};

static enum EdsResult EdsArray_resize(struct EdsArray *arr);

enum EdsResult EdsArray_new(struct EdsArray **arr, size_t initial_capacity) {
    if (initial_capacity == 0) {
        return EDS_ERROR_INVALID_PARAMETER;
    }

    struct EdsArray *new_arr = malloc(sizeof(struct EdsArray));
    if (new_arr == NULL) {
        return EDS_ERROR_MALLOC_FAILED;
    }

    new_arr->data = malloc(sizeof(int) * initial_capacity);
    if (new_arr->data == NULL) {
        free(new_arr);
        return EDS_ERROR_MALLOC_FAILED;
    }

    *arr = new_arr;

    (*arr)->capacity = initial_capacity;
    (*arr)->size = 0;

    return EDS_SUCCESS;
}

enum EdsResult EdsArray_append(struct EdsArray *arr, int value) {
    if (arr == NULL || arr->data == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    if (arr->size == arr->capacity) {
        enum EdsResult r;
        if ((r = EdsArray_resize(arr)) != 0) {
            return r;
        }
    }

    arr->data[arr->size++] = value;
    return EDS_SUCCESS;
}

enum EdsResult EdsArray_insert(struct EdsArray *arr, size_t index, int value) {
    if (arr == NULL || arr->data == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    if (index > arr->size) {
        return EDS_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (arr->size == arr->capacity) {
        enum EdsResult r;
        if ((r = EdsArray_resize(arr)) != 0) {
            return r;
        }
    }

    for (size_t i = arr->size; i > index; --i) {
        arr->data[i] = arr->data[i-1];
    }

    arr->data[index] = value;
    arr->size++;

    return EDS_SUCCESS;
}

enum EdsResult EdsArray_pop(struct EdsArray *arr, int *removed_value) {
    if (arr == NULL || arr->data == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    if (arr->size == 0) {
        return EDS_ELEMENT_NOT_FOUND;
    }

    arr->size--;

    if (removed_value != NULL) {
        *removed_value = arr->data[arr->size];
    }

    return EDS_SUCCESS;
}

enum EdsResult EdsArray_remove(struct EdsArray *arr, int value, int *removed_value) {
    if (arr == NULL || arr->data == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    for (size_t i = 0; i < arr->size; ++i) {
        if (arr->data[i] == value) {
            return EdsArray_remove_at(arr, i, removed_value);
        }
    }

    return EDS_ELEMENT_NOT_FOUND;
}

enum EdsResult EdsArray_remove_at(struct EdsArray *arr, size_t index, int *removed_value) {
    if (arr == NULL || arr->data == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    if (index >= arr->size) {
        return EDS_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (removed_value != NULL) {
        *removed_value = arr->data[index];
    }

    for (size_t i = index; i < arr->size - 1; ++i) {
        arr->data[i] = arr->data[i+1];
    }

    arr->size--;

    return EDS_SUCCESS;
}

enum EdsResult EdsArray_free(struct EdsArray *arr) {
    if (arr == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;

    free(arr);

    return EDS_SUCCESS;
}

enum EdsResult EdsArray_clear(struct EdsArray *arr) {
    if (arr == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    arr->size = 0;
    return EDS_SUCCESS;
}

enum EdsResult EdsArray_get(const struct EdsArray *arr, size_t index, int *value) {
    if (arr == NULL || arr->data == NULL || value == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    if (index >= arr->size) {
        return EDS_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    *value = arr->data[index];
    return EDS_SUCCESS;
}

enum EdsResult EdsArray_set(struct EdsArray *arr, size_t index, int value, int *old_value) {
    if (arr == NULL || arr->data == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    if (index >= arr->size) {
        return EDS_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (old_value != NULL) {
        *old_value = arr->data[index];
    }

    arr->data[index] = value;
    return EDS_SUCCESS;
}

enum EdsResult EdsArray_size(const struct EdsArray *arr, size_t *result) {
    if (arr == NULL || result == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    *result = arr->size;

    return EDS_SUCCESS;
}

enum EdsResult EdsArray_capacity(const struct EdsArray *arr, size_t *result) {
    if (arr == NULL || result == NULL) {
        return EDS_ERROR_NULL_POINTER_PASSED;
    }

    *result = arr->capacity;

    return EDS_SUCCESS;
}

static enum EdsResult EdsArray_resize(struct EdsArray *arr) {
    if ((SIZE_MAX / (arr->capacity * 2)) < sizeof(int)) {
        return EDS_ERROR_ARITHMETIC_OVERFLOW;
    }

    int *resized_data = realloc(arr->data, arr->capacity * 2 * sizeof(int));
    if (resized_data == NULL) {
        return EDS_ERROR_REALLOC_FAILED;
    }

    arr->data = resized_data;
    arr->capacity *= 2;

    return EDS_SUCCESS;
}
