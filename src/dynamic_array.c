#include "../include/EdS/dynamic_array.h"

EdS_darray_t *EdS_darray_new(size_t initial_capacity) {
    if (initial_capacity == 0) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <EdS_darray_new>.\n");
        return NULL;
    }

    EdS_darray_t *arr = malloc(sizeof(EdS_darray_t));
    if (arr == NULL) {
        fprintf(stderr, "ERROR: `malloc` returned NULL in function <EdS_darray_new>.\n");
        return NULL;
    }

    arr->data = malloc(sizeof(int) * initial_capacity);
    if (arr->data == NULL) {
        fprintf(stderr, "ERROR: `malloc` returned NULL in function <EdS_darray_new>.\n");
        return NULL;
    }

    arr->capacity = initial_capacity;
    arr->size = 0;

    return arr;
}

int EdS_darray_append(EdS_darray_t *arr, int value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <append>.\n");
        return EDS_RETURN_ERROR;
    }

    if (arr->size == arr->capacity) {
        int *resized_data = reallocarray(arr->data, arr->capacity * 2, sizeof(int));
        if (resized_data == NULL) {
            fprintf(stderr, "ERROR: `reallocarray` returned NULL in function <append>.\n");
            return EDS_RETURN_ERROR;
        }
        arr->data = resized_data;
        arr->capacity *= 2;
    }

    arr->data[arr->size++] = value;
    return EDS_RETURN_SUCCESS;
}

int EdS_darray_insert(EdS_darray_t *arr, size_t index, int value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <insert>.\n");
        return EDS_RETURN_ERROR;
    }

    if (index > arr->size) {
        fprintf(stderr, "ERROR: invalid <index> in function <insert>.\n");
        return EDS_RETURN_ERROR;
    }

    if (arr->size == arr->capacity) {
        int *resized_data = reallocarray(arr->data, arr->capacity * 2, sizeof(int));
        if (resized_data == NULL) {
            fprintf(stderr, "ERROR: `reallocarray` returned NULL in function <insert>.\n");
            return EDS_RETURN_ERROR;
        }
        arr->data = resized_data;
        arr->capacity *= 2;
    }

    for (size_t i = arr->size; i > index; --i) {
        arr->data[i] = arr->data[i-1];
    }

    arr->data[index] = value;
    arr->size++;

    return EDS_RETURN_SUCCESS;
}

int EdS_darray_pop(EdS_darray_t *arr, int *removed_value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <pop>.\n");
        return EDS_RETURN_ERROR;
    }

    if (arr->size == 0) {
        fprintf(stderr, "ERROR: parameter `arr` is empty in function <pop>.\n");
        return EDS_RETURN_ERROR;
    }

    arr->size--;

    if (removed_value != NULL) {
        *removed_value = arr->data[arr->size];
    }

    return EDS_RETURN_SUCCESS;
}

int EdS_darray_remove(EdS_darray_t *arr, int value, int *removed_value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <remove_value>.\n");
        return EDS_RETURN_ERROR;
    }

    for (size_t i = 0; i < arr->size; ++i) {
        if (arr->data[i] == value) {
            return EdS_darray_remove_at(arr, i, removed_value);
        }
    }

    fprintf(stderr, "ERROR: `value` %d not found in `arr`.\n", value);
    return EDS_RETURN_ERROR;
}

int EdS_darray_remove_at(EdS_darray_t *arr, size_t index, int *removed_value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <remove_at>.\n");
        return EDS_RETURN_ERROR;
    }

    if (index >= arr->size) {
        fprintf(stderr, "ERROR: invalid <index> in function <remove_at>.\n");
        return EDS_RETURN_ERROR;
    }

    if (removed_value != NULL) {
        *removed_value = arr->data[index];
    }

    for (size_t i = index; i < arr->size - 1; ++i) {
        arr->data[i] = arr->data[i+1];
    }

    arr->size--;

    return EDS_RETURN_SUCCESS;
}

int EdS_darray_free(EdS_darray_t *arr) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <destroy_darray>.\n");
        return EDS_RETURN_ERROR;
    }

    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;

    free(arr);
    arr = NULL;

    return EDS_RETURN_SUCCESS;
}

int EdS_darray_clear(EdS_darray_t *arr) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <clear>.\n");
        return EDS_RETURN_ERROR;
    }

    arr->size = 0;
    return EDS_RETURN_SUCCESS;
}

int EdS_darray_get(const EdS_darray_t *arr, size_t index, int *value) {
    if (arr == NULL || arr->data == NULL || value == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <get>.\n");
        return EDS_RETURN_ERROR;
    }

    if (index >= arr->size) {
        fprintf(stderr, "ERROR: invalid <index> in function <get>.\n");
        return EDS_RETURN_ERROR;
    }

    *value = arr->data[index];
    return EDS_RETURN_SUCCESS;
}

int EdS_darray_set(EdS_darray_t *arr, size_t index, int value, int *old_value) {
    if (arr == NULL || arr->data == NULL) {
        fprintf(stderr, "ERROR: NULL pointer passed in function <set>.\n");
        return EDS_RETURN_ERROR;
    }

    if (index >= arr->size) {
        fprintf(stderr, "ERROR: invalid <index> in function <set>.\n");
        return EDS_RETURN_ERROR;
    }

    if (old_value != NULL) {
        *old_value = arr->data[index];
    }

    arr->data[index] = value;
    return EDS_RETURN_SUCCESS;
}

void EdS_darray_print_info(EdS_darray_t *arr) {
    if (arr == NULL) {
        printf("ERROR: parameter `arr` is NULL in function <print_info>.\n");
        exit(EXIT_FAILURE);
    }

    printf("Capacity: %zu\n", arr->capacity);
    printf("Size: %zu\n", arr->size);
}

void EdS_darray_traverse(EdS_darray_t *arr) {
    if (arr == NULL) {
        printf("ERROR: parameter `arr` is NULL in function <traverse>.\n");
        exit(EXIT_FAILURE);
    }

    if (arr->data == NULL) {
        printf("ERROR: parameter `arr->data` is NULL in function <traverse>.\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < arr->size; ++i) {
        printf("%d\n", arr->data[i]);
    }
}
