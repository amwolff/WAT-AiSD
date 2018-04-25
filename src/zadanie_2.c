#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *head, int data);

int pop(struct node *head);

void clean(struct node *head);

void three2one(struct node *result, struct node *head0, struct node *head1, struct node *head2);

int main() {
    struct node *root0 = malloc(sizeof(struct node));
    root0->next = NULL;

    struct node *root1 = malloc(sizeof(struct node));
    root1->next = NULL;

    struct node *root2 = malloc(sizeof(struct node));
    root2->next = NULL;

    struct node *root3 = malloc(sizeof(struct node));
    root3->next = NULL;

    int n0, n1, n2;
    do {
        printf("Kolejna cyfra pierwszej liczby (wpisz -1 aby skończyć):\n");
        scanf("%d", &n0);
        if (n0 == -1) {
            break;
        }
        push(root0, n0);
    } while (1);
    do {
        printf("Kolejna cyfra drugiej liczby (wpisz -1 aby skończyć):\n");
        scanf("%d", &n1);
        if (n1 == -1) {
            break;
        }
        push(root1, n1);
    } while (1);
    do {
        printf("Kolejna cyfra trzeciej liczby (wpisz -1 aby skończyć):\n");
        scanf("%d", &n2);
        if (n2 == -1) {
            break;
        }
        push(root2, n2);
    } while (1);

    three2one(root3, root0, root1, root2);

    printf("\n");
    while (root3->next != NULL) {
        printf("%d", pop(root3));
    }
    printf("\n");

    clean(root0);
    clean(root1);
    clean(root2);
    clean(root3);
    return 0;
}

void three2one(struct node *result, struct node *head0, struct node *head1, struct node *head2) {
    int d0, d1, d2;
    int decs = 0, sum = 0;
    int ret0 = 1, ret1 = 1, ret2 = 1;
    while (ret0 || ret1 || ret2) {
        if (ret0) {
            d0 = pop(head0);
            if (d0 == -1) {
                ret0 = 0;
            } else {
                sum += d0;
            }
        }
        if (ret1) {
            d1 = pop(head1);
            if (d1 == -1) {
                ret1 = 0;
            } else {
                sum += d1;
            }
        }
        if (ret2) {
            d2 = pop(head2);
            if (d2 == -1) {
                ret2 = 0;
            } else {
                sum += d2;
            }
        }

        sum += decs;
        decs = 0;

        for (;;) {
            if (sum >= 10) {
                sum -= 10;
                decs += 1;
            } else {
                break;
            }
        }

        push(result, sum);
        sum = 0;
    }
}

void push(struct node *head, int data) {
    struct node *tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    struct node *new = malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;
    tmp->next = new;
}

int pop(struct node *head) {
    struct node *tmp = head;
    int data;

    if (tmp->next == NULL) {
        return -1;
    }

    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }
    data = tmp->next->data;
    free(tmp->next);
    tmp->next = NULL;
    return data;
}

void clean(struct node *head) {
    while (head->next != NULL) {
        pop(head);
    }
}