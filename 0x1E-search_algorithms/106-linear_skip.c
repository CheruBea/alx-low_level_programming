#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the skiplist_s structure for the singly linked list with an express lane
typedef struct skiplist_s {
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
skiplist_t *linear_skip(skiplist_t *list, int value);

// Function to create a node for the skip list
skiplist_t *create_node(int n, size_t index);

// Function to free a node and its express lane
void free_node(skiplist_t *node);

// Function to print a node
void print_node(const skiplist_t *node);

// Function to print a node and its express lane
void print_node_and_express(const skiplist_t *node);

// Function to calculate the express lane size
int calculate_express_lane_size(int size);

int main(void) {
    // Example usage of the linear_skip function
    int array[] = {0, 1, 2, 3, 4, 7, 12, 15, 18, 19, 23, 53, 61, 62, 76, 99};
    size_t size = sizeof(array) / sizeof(array[0]);
    skiplist_t *list = create_skiplist(array, size);

    // Test print_skiplist
    printf("Skip List:\n");
    print_skiplist(list);

    skiplist_t *result = linear_skip(list, 53);
    if (result)
        printf("Found %d at index: %lu\n", 53, result->index);
    else
        printf("%d not found in the list\n", 53);

    result = linear_skip(list, 2);
    if (result)
        printf("Found %d at index: %lu\n", 2, result->index);
    else
        printf("%d not found in the list\n", 2);

    result = linear_skip(list, 999);
    if (result)
        printf("Found %d at index: %lu\n", 999, result->index);
    else
        printf("%d not found in the list\n", 999);

    // Test linear_skip with NULL pointer
    result = linear_skip(NULL, 0);
    if (result)
        printf("Found %d at index: %lu\n", 0, result->index);
    else
        printf("NULL pointer passed to linear_skip\n");

    free_skiplist(list);
    return 0;
}

skiplist_t *create_skiplist(int *array, size_t size) {
    if (!array || size == 0)
        return NULL;

    // Calculate the size of express lane
    int express_lane_size = calculate_express_lane_size(size);

    // Create head node
    skiplist_t *head = create_node(array[0], 0);
    if (!head)
        return NULL;

    skiplist_t *current = head;
    skiplist_t *express = head;

    // Create the skip list nodes
    for (size_t i = 1; i < size; i++) {
        current->next = create_node(array[i], i);
        if (!current->next) {
            free_skiplist(head);
            return NULL;
        }
        current = current->next;

        if ((i % express_lane_size) == 0) {
            express->express = current;
            express = current;
        }
    }

    return head;
}

void print_skiplist(const skiplist_t *list) {
    const skiplist_t *current = list;
    while (current) {
        print_node_and_express(current);
        current = current->next;
    }
}

void free_skiplist(skiplist_t *list) {
    skiplist_t *current = list;
    while (current) {
        skiplist_t *next = current->next;
        free_node(current);
        current = next;
    }
}

skiplist_t *linear_skip(skiplist_t *list, int value) {
    if (!list)
        return NULL;

    skiplist_t *current = list;
    skiplist_t *express_current = list->express;

    while (express_current && value > express_current->n) {
        current = express_current;
        express_current = express_current->express;
    }

    while (current->next && current->next->n < value)
        current = current->next;

    if (current->next && current->next->n == value)
        return current->next;

    return NULL;
}

skiplist_t *create_node(int n, size_t index) {
    skiplist_t *node = (skiplist_t *)malloc(sizeof(skiplist_t));
    if (!node)
        return NULL;

    node->n = n;
    node->index = index;
    node->next = NULL;
    node->express = NULL;
    return node;
}

void free_node(skiplist_t *node) {
    if (node)
        free(node);
}

void print_node(const skiplist_t *node) {
    if (node)
        printf("n=%d, index=%lu\n", node->n, node->index);
}

void print_node_and_express(const skiplist_t *node) {
    if (node) {
        printf("n=%d, index=%lu", node->n, node->index);
        if (node->express)
            printf(", express=%lu", node->express->index);
        printf("\n");
    }
}

int calculate_express_lane_size(int size) {
    // Calculate express lane size (sqrt(size))
    return (int)sqrt(size);
}
