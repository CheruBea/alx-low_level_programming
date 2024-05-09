#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the node structure for the skip list
typedef struct nodeTag {
    int key;                // Key used for searching
    struct nodeTag *forward[1]; // Skip list forward pointer
} nodeType;

// Define the skip list structure
typedef struct {
    nodeType *hdr;              // List Header
    int listLevel;              // Current level of list
} SkipList;

// Define the skiplist_s structure for the singly linked list with an express lane
typedef struct skiplist_s
{
    int n;
    size_t index;
    struct skiplist_s *next;
    struct skiplist_s *express;
} skiplist_t;

// Function prototype for creating a skip list
skiplist_t *create_skiplist(int *array, size_t size);

// Function prototype for printing a skip list
void print_skiplist(const skiplist_t *list);

// Function prototype for freeing a skip list
void free_skiplist(skiplist_t *list);

// Function to search for a value in a skip list
skiplist_t *linear_skip(skiplist_t *list, int value) {
    if (!list) {
        return NULL;
    }

    skiplist_t *current = list;
    skiplist_t *express_current = list->express;

    while (express_current && value >= express_current->n) {
        printf("Value checked at index [%lu] = [%d]\n", express_current->index, express_current->n);
        current = express_current;
        express_current = express_current->express;
    }

    if (!express_current || value < express_current->n) {
        return NULL;
    }

    while (current->next && current->next->n < value) {
        printf("Value checked at index [%lu] = [%d]\n", current->next->index, current->next->n);
        current = current->next;
    }

    printf("Value found between indexes [%lu] and [%lu]\n", current->index, current->next? current->next->index : -1);
    return current;
}

int main(void) {
    // Example usage of the linear_skip function
    // Assuming create_skiplist and print_skiplist functions are implemented elsewhere
    int array[] = {0, 1, 2, 3, 4, 7, 12, 15, 18, 19, 23, 53, 61, 62, 76, 99};
    size_t size = sizeof(array) / sizeof(array[0]);
    skiplist_t *list = create_skiplist(array, size);
    print_skiplist(list);

    skiplist_t *result = linear_skip(list, 53);
    printf("Found %d at index: %lu\n\n", 53, result->index);

    result = linear_skip(list, 2);
    printf("Found %d at index: %lu\n\n", 2, result->index);

    result = linear_skip(list, 999);
    printf("Found %d at index: %p\n", 999, (void *)result);

    free_skiplist(list);
    return 0;
}

