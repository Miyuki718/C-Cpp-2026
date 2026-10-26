#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int value;
    struct Node *next;
}Node;

Node *head = NULL;
Node *tail = NULL;

void insertAtTail(int v) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    node->value = v;
    node->next = NULL;
    tail->next = node;
    tail = node;
}

void printNode(Node *node) {
    while (node != NULL) {
        printf("%d\n", node->value);
        node = node->next;
    }
    printf("NULL");
    printf("\n");
}

Node *reverseNode(Node *head) {
    Node *previous = NULL;
    Node *current = head;
    while (current != NULL) {
        Node *nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }
    return previous;
}

int findFive(Node *head, int start) {
    Node *current = head;
    int i = 1;

    while (current != NULL) {
        if (i >= start && current->value == 5) {
            return i;
        }

        current = current->next;
        i++;
    }

    return -1;
}

int main() {
    int values[] = {2, 5, 3, 5, 7, 5};
    int count = sizeof(values)/sizeof(values[0]);
    Node *node=malloc(sizeof (Node));
    node->value = values[0];
    node->next = NULL;
    head = node;
    tail = node;
    for (int i = 0; i < count; i++) {
        insertAtTail(values[i]);
    }
    printNode(head);    //创建并打印

    tail = head;
    head = reverseNode(head);
    printf("Reversed list:\n");
    printNode(head);    //反转并打印

    int first = findFive(head, 1);
    if (first == -1) {
        printf("There is no 5!\n");
    } else {
        printf("First 5: position %d\n", first);

        int second = findFive(head, first + 1);

        if (second == -1) {
            printf("There is no next 5!\n");
        } else {
            printf("Next 5: position %d\n", second);
        }
    }   //找5

    Node *current = head;
    while (current != NULL) {
        Node *nextNode = current->next;
        free(current);
        current = nextNode;
    }

    head = NULL;
    tail = NULL;    //释放节点

    return 0;
}