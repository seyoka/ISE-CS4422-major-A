#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node* createNode(char* val);
void addToEnd(struct Node** head, struct Node* nextNode);
void deleteNode(struct Node** head, struct Node* nodeToDelete);

#endif
