#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

struct node *node_alloc(int value) {
    struct node *newnode = malloc(sizeof(struct node));
    if (newnode != NULL) {
        newnode->value = value;
        newnode->next = NULL;
    }
    return newnode;
}

void node_free(struct node *n) {
    free(n);
}

void llist_insert_head(struct node **head, struct node *n) {
    n->next = *head; //new node next to head
    *head = n; //head pointer is now new node
}

struct node *llist_delete_head(struct node **head) {
    if (*head == NULL) {
        return NULL;
    }
    struct node *old_head = *head;
    *head = old_head->next;
    return old_head; //wanna be a young cat !!
}

void llist_insert_tail(struct node **head, struct node *n) {
    if (*head == NULL) {
        *head = n;
    } else {
        struct node *current = *head;
        while (current->next != NULL) { //traverse 
            current = current->next;
        }
        current->next = n;
    }
}

void llist_print(struct node *head) {
    struct node *current = head;

    if (current == NULL) {
        printf("[Empty list]\n");
        return;
    }

    int place = 0;
    while (current != NULL) {
        char *spacer = malloc((place + 1) * 4 + 1);
        memset(spacer, ' ', (place + 1) * 4);
        spacer[(place + 1) * 4] = '\0';

        printf("%d: %s -> %d\n", place, spacer, current->value);
        place++;
        current = current->next;

        free(spacer);
    }
}

void llist_free(struct node **head) {
    struct node *current = *head;
    struct node *next; //cus node.next is innacessible after free
    while (current != NULL) {
        next = current->next;
        node_free(current);
        current = next;
    }
    *head = NULL;
}

int main(int argc, char *argv[]) {
    struct node *head = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "ih") == 0) {
            struct node *n = node_alloc(atoi(argv[++i]));
            llist_insert_head(&head, n);
        } else if (strcmp(argv[i], "it") == 0) {
            struct node *n = node_alloc(atoi(argv[++i]));
            llist_insert_tail(&head, n);
        } else if (strcmp(argv[i], "dh") == 0) {
            struct node *n = llist_delete_head(&head);
            if (n != NULL) {
                node_free(n);
            }
        } else if (strcmp(argv[i], "f") == 0) {
            llist_free(&head);
        } else if (strcmp(argv[i], "p") == 0) {
            llist_print(head);
        }
    }

    return 0;
}