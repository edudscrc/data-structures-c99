#include <stdio.h>
#include <stdlib.h>
#include "../include/EdS/dynamic_array.h"

struct EdsArray {
    int *data;
    size_t size;
    size_t capacity;
};

struct EdsArray *EdsArray_new(size_t initial_capacity) {
    if (initial_capacity == 0) {
        fprintf(stderr, "ERROR: <initial_capacity> can't be 0 in function <EdsArray_new>.\n");
        return NULL;
    }

    struct EdsArray *arr = malloc(sizeof(struct EdsArray));
    if (arr == NULL) {
        fprintf(stderr, "ERROR: `malloc` returned NULL in function <EdsArray_new>.\n");
        return NULL;
    }

    arr->data = malloc(sizeof(int) * initial_capacity);
    if (arr->data == NULL) {
        free(arr);
        fprintf(stderr, "ERROR: `malloc` returned NULL in function <EdsArray_new>.\n");
        return NULL;
    }

    arr->capacity = initial_capacity;
    arr->size = 0;

    return arr;
}

enum EdsResult EdsArray_append(struct EdsArray *arr, int value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <append>.\n");
        return EDS_FAIL;
    }

    if (arr->size == arr->capacity) {
        int *resized_data = reallocarray(arr->data, arr->capacity * 2, sizeof(int));
        if (resized_data == NULL) {
            fprintf(stderr, "ERROR: `reallocarray` returned NULL in function <append>.\n");
            return EDS_FAIL;
        }
        arr->data = resized_data;
        arr->capacity *= 2;
    }

    arr->data[arr->size++] = value;
    return EDS_SUCCESS;
}

enum EdsResult EdsArray_insert(struct EdsArray *arr, size_t index, int value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <insert>.\n");
        return EDS_FAIL;
    }

    if (index > arr->size) {
        fprintf(stderr, "ERROR: invalid <index> in function <insert>.\n");
        return EDS_FAIL;
    }

    if (arr->size == arr->capacity) {
        int *resized_data = reallocarray(arr->data, arr->capacity * 2, sizeof(int));
        if (resized_data == NULL) {
            fprintf(stderr, "ERROR: `reallocarray` returned NULL in function <insert>.\n");
            return EDS_FAIL;
        }
        arr->data = resized_data;
        arr->capacity *= 2;
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
        fprintf(stderr, "ERROR: NULL pointer passed in function <pop>.\n");
        return EDS_FAIL;
    }

    if (arr->size == 0) {
        fprintf(stderr, "ERROR: parameter `arr` is empty in function <pop>.\n");
        return EDS_FAIL;
    }

    arr->size--;

    if (removed_value != NULL) {
        *removed_value = arr->data[arr->size];
    }

    return EDS_SUCCESS;
}

enum EdsResult EdsArray_remove(struct EdsArray *arr, int value, int *removed_value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <remove_value>.\n");
        return EDS_FAIL;
    }

    for (size_t i = 0; i < arr->size; ++i) {
        if (arr->data[i] == value) {
            return EdsArray_remove_at(arr, i, removed_value);
        }
    }

    fprintf(stderr, "ERROR: `value` %d not found in `arr`.\n", value);
    return EDS_FAIL;
}

enum EdsResult EdsArray_remove_at(struct EdsArray *arr, size_t index, int *removed_value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <remove_at>.\n");
        return EDS_FAIL;
    }

    if (index >= arr->size) {
        fprintf(stderr, "ERROR: invalid <index> in function <remove_at>.\n");
        return EDS_FAIL;
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
        fprintf(stderr, "ERROR: NULL pointer passed in function <destroy_darray>.\n");
        return EDS_FAIL;
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
        fprintf(stderr, "ERROR: NULL pointer passed in function <clear>.\n");
        return EDS_FAIL;
    }

    arr->size = 0;
    return EDS_SUCCESS;
}

enum EdsResult EdsArray_get(const struct EdsArray *arr, size_t index, int *value) {
    if (arr == NULL || arr->data == NULL || value == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <get>.\n");
        return EDS_FAIL;
    }

    if (index >= arr->size) {
        fprintf(stderr, "ERROR: invalid <index> in function <get>.\n");
        return EDS_FAIL;
    }

    *value = arr->data[index];
    return EDS_SUCCESS;
}

enum EdsResult EdsArray_set(struct EdsArray *arr, size_t index, int value, int *old_value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <set>.\n");
        return EDS_FAIL;
    }

    if (index >= arr->size) {
        fprintf(stderr, "ERROR: invalid <index> in function <set>.\n");
        return EDS_FAIL;
    }

    if (old_value != NULL) {
        *old_value = arr->data[index];
    }

    arr->data[index] = value;
    return EDS_SUCCESS;
}

enum EdsResult EdsArray_size(const struct EdsArray *arr, size_t *result) {
    if (arr == NULL || result == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <size>.\n");
        return EDS_FAIL;
    }

    *result = arr->size;

    return EDS_SUCCESS;
}

enum EdsResult EdsArray_capacity(const struct EdsArray *arr, size_t *result) {
    if (arr == NULL || result == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <capacity>.\n");
        return EDS_FAIL;
    }

    *result = arr->capacity;

    return EDS_SUCCESS;
}
