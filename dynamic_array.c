#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *array;
    size_t capacity;
    size_t size;
} array_list;

array_list create_array_list(size_t capacity);
void push(array_list *list, int n);
int pop(array_list *list, bool *error);
void resize_array_list(array_list *list, int factor);
void insert(array_list *list, int index, int element);
void print_array_list(array_list *list);
void unload_array_list(array_list *list);

int main(void) {
    array_list list = create_array_list(4);
    push(&list, 3);
    push(&list, 4);

    print_array_list(&list);
    printf("Size: %zu, Capacity: %zu\n", list.size, list.capacity);

    push(&list, 9);
    push(&list, 6);
    print_array_list(&list);
    printf("Size: %zu, Capacity: %zu\n", list.size, list.capacity);

    push(&list, 11);
    push(&list, 7);
    print_array_list(&list);
    printf("Size: %zu, Capacity: %zu\n", list.size, list.capacity);

    bool error_popping = false;

    printf("Pop: %i\n", pop(&list, &error_popping));
    if (error_popping) {
        unload_array_list(&list);
        printf("Error trying to pop element\n");
        return -1;
    }

    print_array_list(&list);
    printf("Size: %zu, Capacity: %zu\n", list.size, list.capacity);

    // pop(&list, &error_popping);
    // pop(&list, &error_popping);
    // pop(&list, &error_popping);
    // pop(&list, &error_popping);
    // pop(&list, &error_popping);
    // pop(&list, &error_popping);

    // if (error_popping) {
    //     unload_array_list(&list);
    //     printf("Error trying to pop element\n");
    //     return -1;
    // }

    insert(&list, 0, 2);
    print_array_list(&list);
    printf("Size: %zu, Capacity: %zu\n", list.size, list.capacity);

    insert(&list, 7, 15);
    print_array_list(&list);
    printf("Size: %zu, Capacity: %zu\n", list.size, list.capacity);

    insert(&list, 6, 12);
    print_array_list(&list);
    printf("Size: %zu, Capacity: %zu\n", list.size, list.capacity);

    printf("Size: %zu, Capacity: %zu\n", list.size, list.capacity);
    printf("???%i\n", list.array[8]);

    unload_array_list(&list);

    printf("%p\n", list.array);
}

void print_array_list(array_list *list) {
    printf("[ ");
    for (int i = 0; i < list->size; i++) {
        if (i == list->size - 1) {
            printf("%i", list->array[i]);
        } else {
            printf("%i, ", list->array[i]);
        }
    }
    printf(" ]\n");
}

array_list create_array_list(size_t capacity) {
    array_list list; 
    list.array = malloc(capacity * sizeof(int));
    if (list.array == NULL) {
        exit(-1);
    }
    list.capacity = capacity;
    list.size = 0;
    return list;
}

void resize_array_list(array_list *list, int factor) {
    list->capacity = list->capacity * factor;
    list->array = realloc(list->array, sizeof(int) * list->capacity);
    if (list->array == NULL) {
        exit(-1);
    }
}

void push(array_list *list, int element) {
    if (list->capacity == list->size) {
        resize_array_list(list, 2);
    }
    list->array[list->size] = element;
    list->size++;
}

int pop(array_list *list, bool *error) {
    if (list->size == 0) {
        *error = true;
        return 0;
    }
    int element = list->array[list->size - 1];
    list->size--;
    return element;
}

void insert(array_list *list, int index, int element) {
    if (index < 0 || index > list->capacity - 1) {
        return;
    }

    list->size++;

    if (list->capacity == list->size) {
        resize_array_list(list, 2);
    }

    int current_element_at_index = list->array[index];

    list->array[index] = element;

    if (index > list->size) {
        return;
    }

    for (int i = index + 1; i < list->capacity; i++) {
        int previous_element = list->array[i];
        list->array[i] = current_element_at_index;
        current_element_at_index = previous_element;
    }
}

void unload_array_list(array_list *list) {
    free(list->array);
    list->array = NULL;
}