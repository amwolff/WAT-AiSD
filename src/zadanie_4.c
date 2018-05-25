#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *head, int data);

void bubblesort(struct node *head);

void insertionsort(struct node *head);

void sllprint(struct node *head);

int main() {
    int m;
    printf("m:\n>");
    scanf("%d", &m);
    struct node *root = malloc(sizeof(struct node));
    root->data = -1;
    root->next = NULL;
    srand(time(NULL));
    for (int i = 0; i <= m; ++i) {
        push(root, rand() % 21);
    }

    int n;
    printf("n (0 - bubble sort / 1 - insertion sort:\n>");
    scanf("%d", &n);

    sllprint(root);
    printf("\n\n\n");
    if (n == 0) {
        bubblesort(root);
    } else if (n == 1) {
        insertionsort(root);
    } else {
        return 1;
    }
    sllprint(root);

    return 0;
}

void push(struct node *head, int data) {
    struct node *tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        exit(1);
    }
    new->data = data;
    new->next = NULL;
    tmp->next = new;
}

void bubblesort(struct node *head) {
    struct node *tmp0 = head;
    while (tmp0->next != NULL) {
        struct node *tmp1 = tmp0->next;
        while (tmp1->next != NULL) {
            if (tmp0->data > tmp1->data) {
                int x = tmp0->data;
                tmp0->data = tmp1->data;
                tmp1->data = x;
            }
            tmp1 = tmp1->next;
        }
        tmp0 = tmp0->next;
    }
}

struct node *pop(struct node *head) {
    struct node *tmp = head;
    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }
    struct node *ret = tmp->next;
    tmp->next = NULL;
    return ret;
}

void insertionsort(struct node *head) {
    struct node *sorted = malloc(sizeof(struct node));
    if (sorted == NULL) {
        exit(1);
    }
    sorted->data = -1;
    sorted->next = NULL;

    struct node *last0 = pop(head);
    sorted->next = last0;

    while (head->next != NULL) {
        struct node *last1 = pop(head);
        struct node *temp = sorted;
        while (temp->next != NULL && last1->data >= temp->next->data) {
            temp = temp->next;
        }
        last1->next = temp->next;
        temp->next = last1;
    }
    head->next = sorted->next;
    free(sorted);
}

void sllprint(struct node *head) {
    struct node *tmp = head->next;
    printf("%d ", tmp->data);
    while (tmp->next != NULL) {
        tmp = tmp->next;
        printf("%d ", tmp->data);
    }
}