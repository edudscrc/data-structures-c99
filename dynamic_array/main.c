#include "eds_dynamic_array.h"

#define INITIAL_CAPACITY 5
#define AMOUNT_TO_INSERT 30

int main(void) {
    EdS_dynamic_array_t* my_array = EdS_dynamic_array_new(INITIAL_CAPACITY);

    for (int i = 0; i < AMOUNT_TO_INSERT; ++i) {
        EdS_dynamic_array_append(my_array, i * 2);
    }

    EdS_dynamic_array_print_info(my_array);

    EdS_dynamic_array_traverse(my_array);

    EdS_dynamic_array_remove_at(my_array, 4, NULL);
    EdS_dynamic_array_remove_at(my_array, 14, NULL);

    EdS_dynamic_array_remove(my_array, 42, NULL);

    EdS_dynamic_array_insert(my_array, 8, 100);
    EdS_dynamic_array_insert(my_array, my_array->size, 9767);

    EdS_dynamic_array_traverse(my_array);

    EdS_dynamic_array_pop(my_array, NULL);
    EdS_dynamic_array_pop(my_array, NULL);
    EdS_dynamic_array_pop(my_array, NULL);

    EdS_dynamic_array_print_info(my_array);

    EdS_dynamic_array_traverse(my_array);

    EdS_dynamic_array_free(my_array);

    return 0;
}
