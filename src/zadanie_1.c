#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

void push(struct node *head, int data);

void move_right(struct node *head, int n, int k);

void move_left(struct node *head, int n, int k);

void traverse_right_and_print(struct node *head);

void traverse_left_and_print(struct node *head);

void push(struct node *head, int data) {
    struct node *tmp = head;

    while (tmp->next != head) {
        tmp = tmp->next;
    }

    struct node *new = malloc(sizeof(struct node));

    tmp->next = new;
    head->prev = new;

    new->prev = tmp;
    new->next = head;
    new->data = data;
}

void move_right(struct node *head, int n, int k) {
    struct node *tmp = head;
    for (int i = 1; i <= n; ++i) {
        if (i == n) {
            struct node *e = tmp;
            struct node *l = e->prev;
            struct node *r = e->next;
            l->next = r;
            r->prev = l;
            for (int j = 1; j <= k; ++j) {
                tmp = tmp->next;
                if (j == k) {
                    struct node *right = tmp->next;
                    tmp->next = e;
                    right->prev = e;
                    e->next = right;
                    e->prev = tmp;
                    break;
                }
            }
            break;
        }
        tmp = tmp->next;
    }
}

void move_left(struct node *head, int n, int k) {
    struct node *tmp = head;
    for (int i = 1; i <= n; ++i) {
        if (i == n) {
            struct node *e = tmp;
            struct node *l = e->prev;
            struct node *r = e->next;
            l->next = r;
            r->prev = l;
            for (int j = 1; j <= k; ++j) {
                tmp = tmp->prev;
                if (j == k) {
                    struct node *right = tmp->next;
                    tmp->next = e;
                    right->prev = e;
                    e->next = right;
                    e->prev = tmp;
                    break;
                }
            }
            break;
        }
        tmp = tmp->prev;
    }
}

void traverse_right_and_print(struct node *head) {
    struct node *tmp = head;
    while (1) {
        if (tmp->next == head) {
            printf("%d", tmp->data);
            break;
        }
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
}


void traverse_left_and_print(struct node *head) {
    struct node *tmp = head;
    while (1) {
        if (tmp->prev == head) {
            printf("%d", tmp->data);
            break;
        }
        printf("%d ", tmp->data);
        tmp = tmp->prev;
    }
}

int main() {
    struct node *root = malloc(sizeof(struct node));
    root->next = root;
    root->prev = root;

    int m, n, k;
    char kier = '\0';

    printf("Wartość m:\n> ");
    scanf("%d", &m);
    printf("Wartość n:\n> ");
    scanf("%d", &n);
    printf("Wartość kier:\n> ");
    scanf("%c", &kier);
    printf("Wartość k:\n> ");
    scanf("%d", &k);

    root->data = -1;
    for (int i = 0; i < m; ++i) {
        push(root, i);
    }

    free(root);
    return 0;
}