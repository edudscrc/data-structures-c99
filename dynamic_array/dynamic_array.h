#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct DynamicArray {
    int* data;
    size_t size;
    size_t capacity;
} DynamicArray;

void init_dynamic_array(DynamicArray* array, size_t initial_capacity);

void append(DynamicArray* array, int value);
void insert_at(DynamicArray* array, int value, int index);
void remove_value(DynamicArray* array, int value);
void remove_at(DynamicArray* array, int index);
void remove_last(DynamicArray* array);

void print_info(DynamicArray* array);
void traverse(DynamicArray* array);

void destroy_dynamic_array(DynamicArray* array);

#endif // DYNAMIC_ARRAY_H
