#include "dynamic_array.h"

#define INITIAL_CAPACITY 5
#define AMOUNT_TO_INSERT 30

int main(void) {
    DynamicArray my_array;
    init_dynamic_array(&my_array, INITIAL_CAPACITY);

    for (int i = 0; i < AMOUNT_TO_INSERT; ++i) {
        append(&my_array, i * 2);
    }

    printf("%zu\n", my_array.capacity);
    printf("%zu\n", my_array.size);

    for (int i = 0; i < my_array.size; ++i) {
        printf("%d\n", my_array.data[i]);
    }

    remove_at(&my_array, 4);
    remove_at(&my_array, 14);

    remove_value(&my_array, 42);

    for (int i = 0; i < my_array.size; ++i) {
        printf("%d\n", my_array.data[i]);
    }

    destroy_dynamic_array(&my_array);

    return 0;
}
