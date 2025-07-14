#include "dynamic_array.h"

#define INITIAL_CAPACITY 5
#define AMOUNT_TO_INSERT 30

int main(void) {
    DynamicArray my_array;
    init_dynamic_array(&my_array, INITIAL_CAPACITY);

    for (int i = 0; i < AMOUNT_TO_INSERT; ++i) {
        append(&my_array, i * 2);
    }

    print_info(&my_array);

    traverse(&my_array);

    remove_at(&my_array, 4);
    remove_at(&my_array, 14);

    remove_value(&my_array, 42);

    insert_at(&my_array, 100, 8);
    insert_at(&my_array, 9767, my_array.size);

    traverse(&my_array);

    remove_last(&my_array);
    remove_last(&my_array);
    remove_last(&my_array);

    print_info(&my_array);

    traverse(&my_array);

    destroy_dynamic_array(&my_array);

    return 0;
}
