#include "../include/EdS/dynamic_array.h"

#define INITIAL_CAPACITY 5
#define AMOUNT_TO_INSERT 30

int main(void) {
    struct EdsArray *my_array = NULL;
    EdsArray_new(&my_array, INITIAL_CAPACITY);

    for (int i = 0; i < AMOUNT_TO_INSERT; ++i) {
        if (EdsArray_append(my_array, i * 2) < 0) {
            EdsArray_free(my_array);
        }
    }

    EdsArray_remove_at(my_array, 4, NULL);
    EdsArray_remove_at(my_array, 14, NULL);

    EdsArray_remove(my_array, 42, NULL);

    EdsArray_insert(my_array, 8, 100);

    size_t my_array_size;
    EdsArray_size(my_array, &my_array_size);

    EdsArray_insert(my_array, my_array_size, 9767);

    EdsArray_pop(my_array, NULL);
    EdsArray_pop(my_array, NULL);
    EdsArray_pop(my_array, NULL);

    EdsArray_free(my_array);

    return 0;
}
