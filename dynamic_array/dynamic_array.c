#include "dynamic_array.h"

void init_dynamic_array(DynamicArray* array, size_t initial_capacity) {
    array->capacity = initial_capacity;
    array->size = 0;

    array->data = malloc(sizeof(int) * initial_capacity);
    if (array->data == NULL) {
        printf("ERROR: `malloc` returned NULL in function <init_dynamic_array>.\n");
        exit(EXIT_FAILURE);
    }
}

void append(DynamicArray* array, int value) {
    if (array == NULL) {
        printf("ERROR: parameter `array` is NULL in function <append>.\n");
        exit(EXIT_FAILURE);
    }

    if (array->data == NULL) {
        printf("ERROR: parameter `array->data` is NULL in function <append>.\n");
        exit(EXIT_FAILURE);
    }

    if (array->size == array->capacity) {
        int* resized_data = reallocarray(array->data, array->capacity * 2, sizeof(int));
        if (resized_data == NULL) {
            printf("ERROR: `reallocarray` returned NULL in function <append>.\n");
            free(array->data);
            exit(EXIT_FAILURE);
        }
        array->data = resized_data;
        array->capacity *= 2;
    }

    array->data[array->size++] = value;
}

void remove_value(DynamicArray* array, int value) {
    if (array == NULL) {
        printf("ERROR: parameter `array` is NULL in function <remove_value>.\n");
        exit(EXIT_FAILURE);
    }

    if (array->data == NULL) {
        printf("ERROR: parameter `array->data` is NULL in function <remove_value>.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < array->size; ++i) {
        if (array->data[i] == value) {
            remove_at(array, i);
            return;
        }
    }

    printf("ERROR: `value` %d not found in `array`.\n", value);
    free(array->data);
    exit(EXIT_FAILURE);
}

void remove_at(DynamicArray* array, int index) {
    if (array == NULL) {
        printf("ERROR: parameter `array` is NULL in function <remove_at>.\n");
        exit(EXIT_FAILURE);
    }

    if (index >= array->size) {
        printf("ERROR: parameter `index` >= array->size in function <remove_at>.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = index; i < array->size - 1; ++i) {
        array->data[i] = array->data[i+1];
    }

    array->size -= 1;
}

void destroy_dynamic_array(DynamicArray* array) {
    if (array == NULL) {
        printf("ERROR: parameter `array` is NULL in function <destroy_dynamic_array>.\n");
        exit(EXIT_FAILURE);
    }

    if (array->data == NULL) {
        printf("ERROR: parameter `array->data` is NULL in function <destroy_dynamic_array>.\n");
        exit(EXIT_FAILURE);
    }

    free(array->data);
    array->data = NULL;
    array->size = 0;
}
