/*
Discussions and practicals for C:
•1) Develop a single-linked list in C to create a stack of usernames
•2) Extend the example to free the memory allocated by the linked list
*/


#include <stdio.h>
#include <stdlib.h>

struct Node {
    char* val;
    struct Node* next;
};

struct Node* createNode(char* val){
    struct Node* newNode = (struct Node* ) malloc(sizeof(struct Node));

    newNode -> val = val ;
    newNode -> next = NULL;

    return newNode;
}

void addToEnd(struct Node** head, struct Node* nextNode){
    if (*head == NULL) {
        *head = nextNode;
        return;
    }

    struct Node* curr = *head;

    while(curr->next != NULL){
        curr = curr->next;
    }

    curr->next = nextNode;
}

void deleteNode(struct Node** head, struct Node* nodeToDelete){

    struct Node* curr = *head;

    while(curr -> next != nodeToDelete){
        curr = curr -> next ;
    }

    curr -> next = nodeToDelete -> next ;
    free(nodeToDelete);
}

void printList(struct Node** head){
    struct Node* curr = *head;
    while (curr != NULL) {
        printf("%s -> ", curr->val);
        curr = curr->next;
    }
}

void freeList(struct Node** head){
    struct Node* curr = *head;
    struct Node* prev;

    while(curr != NULL){
        prev = curr;
        curr = curr -> next;
        free(prev);
    }

    *head = NULL;
}

int main() {

    /*
        * GPT wrote the test case everything is me
    */

    // Initialize an empty list
    struct Node* head = NULL;

    // Test createNode and addToEnd
    struct Node* node1 = createNode("Node 1");
    struct Node* node2 = createNode("Node 2");
    struct Node* node3 = createNode("Node 3");

    addToEnd(&head, node1); // Add node1 to the list
    addToEnd(&head, node2); // Add node2 to the list
    addToEnd(&head, node3); // Add node3 to the list

    printf("List after adding nodes:\n");
    printList(&head);
    printf("NULL\n\n");

    // Test deleteNode
    printf("Deleting 'Node 2'...\n");
    deleteNode(&head, node2);
    printf("List after deleting 'Node 2':\n");
    printList(&head);
    printf("NULL\n\n");

    // Test freeList
    printf("Freeing the list...\n");
    freeList(&head);

    // Verify the list is empty
    if (head == NULL) {
        printf("List successfully freed and is now empty.\n");
    } else {
        printf("List was not freed correctly.\n");
    }

    return 0;
}
