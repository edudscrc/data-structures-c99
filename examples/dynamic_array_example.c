#include "../include/EdS/dynamic_array.h"

#define INITIAL_CAPACITY 5
#define AMOUNT_TO_INSERT 30

int main(void) {
    EdS_darray_t* my_array = EdS_darray_new(INITIAL_CAPACITY);

    for (int i = 0; i < AMOUNT_TO_INSERT; ++i) {
        EdS_darray_append(my_array, i * 2);
    }

    EdS_darray_print_info(my_array);

    EdS_darray_traverse(my_array);

    EdS_darray_remove_at(my_array, 4, NULL);
    EdS_darray_remove_at(my_array, 14, NULL);

    EdS_darray_remove(my_array, 42, NULL);

    EdS_darray_insert(my_array, 8, 100);
    EdS_darray_insert(my_array, my_array->size, 9767);

    EdS_darray_traverse(my_array);

    EdS_darray_pop(my_array, NULL);
    EdS_darray_pop(my_array, NULL);
    EdS_darray_pop(my_array, NULL);

    EdS_darray_print_info(my_array);

    EdS_darray_traverse(my_array);

    EdS_darray_free(my_array);

    return 0;
}
