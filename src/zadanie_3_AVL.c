#include <stdio.h>
#include <stdlib.h>

#define PRINT_DISTANCE 1

struct avl_node {
    int key, data, height;
    struct avl_node *left, *right;
};

struct avl_node *make_avl_node(int key, int data);

struct avl {
    struct avl_node *root;
};

struct avl *make_avl();

struct avl_node *avl_search_wrapper(struct avl *t, int key);

void avl_insert_wrapper(struct avl *t, struct avl_node *n);

void avl_delete_wrapper(struct avl *t, int key);

void avl_clear_wrapper(struct avl *t);

void avl_traversal_NLR_wrapper(struct avl *t);

void avl_traversal_LNR_wrapper(struct avl *t);

void avl_traversal_LRN_wrapper(struct avl *t);

void avl_traversal_custom_wrapper(struct avl *t);

void main_menu();

int main() {
    struct avl *t = make_avl();
    if (t == NULL) {
        return 1;
    }

    main_menu();

    int input0 = '\0';
    int input1;
    int input2_1;
    int input2_2;
    int input3;
    while (input0 != 9) {
        scanf("%d", &input0);

        if (input0 == 1) {
            printf("Klucz:\n>");
            scanf("%d", &input1);
            struct avl_node *n0 = avl_search_wrapper(t, input1);
            if (n0 == NULL) {
                printf("Nie znaleziono\n");
                continue;
            }
            printf("Wynik wyszukiwania: [%d]: %d\n", n0->key, n0->data);
        } else if (input0 == 2) {
            printf("Klucz:\n>");
            scanf("%d", &input2_1);
            printf("Dane:\n>");
            scanf("%d", &input2_2);
            struct avl_node *n1 = make_avl_node(input2_1, input2_2);
            if (n1 == NULL) {
                printf("Nie można było utworzyć węzła\n");
                continue;
            }
            avl_insert_wrapper(t, n1);
        } else if (input0 == 3) {
            printf("Klucz:\n>");
            scanf("%d", &input3);
            avl_delete_wrapper(t, input3);
        } else if (input0 == 4) {
            avl_clear_wrapper(t);
        } else if (input0 == 5) {
            avl_traversal_NLR_wrapper(t);
        } else if (input0 == 6) {
            avl_traversal_LNR_wrapper(t);
        } else if (input0 == 7) {
            avl_traversal_LRN_wrapper(t);
        } else if (input0 == 8) {
            avl_traversal_custom_wrapper(t);
        }
    }

    avl_clear_wrapper(t);
    free(t);
    return 0;
}

struct avl_node *make_avl_node(int key, int data) {
    struct avl_node *n = malloc(sizeof(struct avl_node));
    if (n == NULL) {
        return n;
    }

    n->key = key;
    n->data = data;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;

    return n;
}

struct avl *make_avl() {
    struct avl *t = malloc(sizeof(struct avl));
    if (t == NULL) {
        return t;
    }

    t->root = NULL;

    return t;
}

struct avl_node *avl_search(struct avl_node *r, int key) {
    if (r == NULL || r->key == key) {
        return r;
    } else if (key < r->key) {
        return avl_search(r->left, key);
    }
    return avl_search(r->right, key);
}

struct avl_node *avl_search_wrapper(struct avl *t, int key) {
    return avl_search(t->root, key);
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int avl_height(struct avl_node *n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

struct avl_node *rotate_right(struct avl_node *n) {
    struct avl_node *x = n->left;
    struct avl_node *st = x->right;

    x->right = n;
    n->left = st;

    n->height = 1 + max(avl_height(n->left), avl_height(n->right));
    x->height = 1 + max(avl_height(x->left), avl_height(x->right));
    return x;
}

struct avl_node *rotate_left(struct avl_node *n) {
    struct avl_node *x = n->right;
    struct avl_node *st = x->left;


    x->left = n;
    n->right = st;

    n->height = 1 + max(avl_height(n->left), avl_height(n->right));
    x->height = 1 + max(avl_height(x->left), avl_height(x->right));
    return x;
}

int avl_node_balance(struct avl_node *n) {
    if (n == NULL) {
        return 0;
    }
    return avl_height(n->left) - avl_height(n->right);
}

struct avl_node *avl_insert(struct avl_node *r, struct avl_node *n) {
    if (r == NULL) {
        return n;
    }

    if (n->key < r->key) {
        r->left = avl_insert(r->left, n);
    } else if (n->key > r->key) {
        r->right = avl_insert(r->right, n);
    } else {
        return r;
    }

    r->height = 1 + max(avl_height(r->left), avl_height(r->right));

    int balance = avl_node_balance(r);
    if (balance > 1 && n->key < r->left->key) {
        return rotate_right(r);
    } else if (balance > 1 && n->key > r->left->key) {
        r->left = rotate_left(r->left);
        return rotate_right(r);
    } else if (balance < -1 && n->key > r->right->key) {
        return rotate_left(r);
    } else if (balance < -1 && n->key < r->right->key) {
        r->right = rotate_right(r->right);
        return rotate_left(r);
    }

    return r;
}

void avl_insert_wrapper(struct avl *t, struct avl_node *n) {
    t->root = avl_insert(t->root, n);
}

struct avl_node *avl_search_min(struct avl_node *n) {
    struct avl_node *x = n;
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

struct avl_node *avl_delete(struct avl_node *r, int key) {
    if (r == NULL) {
        return r;
    }

    if (key < r->key) {
        r->left = avl_delete(r->left, key);
    } else if (key > r->key) {
        r->right = avl_delete(r->right, key);
    } else {
        if (r->left == NULL) {
            struct avl_node *x = r->right;
            free(r);
            return x;
        } else if (r->right == NULL) {
            struct avl_node *x = r->left;
            free(r);
            return x;
        }

        struct avl_node *x = avl_search_min(r->right);

        r->key = x->key;
        r->data = x->data;

        r->right = avl_delete(r->right, x->key);
    }

    r->height = 1 + max(avl_height(r->left), avl_height(r->right));

    int balance = avl_node_balance(r);
    if (balance > 1 && avl_node_balance(r->left) >= 0) {
        return rotate_right(r);
    } else if (balance > 1 && avl_node_balance(r->left) < 0) {
        r->left = rotate_left(r->left);
        return rotate_right(r);
    } else if (balance < -1 && avl_node_balance(r->right) <= 0) {
        return rotate_left(r);
    } else if (balance < -1 && avl_node_balance(r->right) > 0) {
        r->right = rotate_right(r->right);
        return rotate_left(r);
    }

    return r;
}

void avl_delete_wrapper(struct avl *t, int key) {
    t->root = avl_delete(t->root, key);
}

void avl_clear(struct avl_node *r) {
    if (r == NULL) {
        return;
    }
    avl_clear(r->left);
    avl_clear(r->right);
    free(r);
}

void avl_clear_wrapper(struct avl *t) {
    avl_clear(t->root);
    t->root = NULL;
}

void avl_traversal_NLR(struct avl_node *n) {
    if (n == NULL) {
        return;
    }
    printf("%d\n", n->key);
    avl_traversal_NLR(n->left);
    avl_traversal_NLR(n->right);
}

void avl_traversal_NLR_wrapper(struct avl *t) {
    avl_traversal_NLR(t->root);
}

void avl_traversal_LNR(struct avl_node *n) {
    if (n == NULL) {
        return;
    }
    avl_traversal_LNR(n->left);
    printf("%d\n", n->key);
    avl_traversal_LNR(n->right);
}

void avl_traversal_LNR_wrapper(struct avl *t) {
    avl_traversal_LNR(t->root);
}

void avl_traversal_LRN(struct avl_node *n) {
    if (n == NULL) {
        return;
    }
    avl_traversal_LRN(n->left);
    avl_traversal_LRN(n->right);
    printf("%d\n", n->key);
}

void avl_traversal_LRN_wrapper(struct avl *t) {
    avl_traversal_LRN(t->root);
}

void avl_traversal_custom(struct avl_node *r, int distance) {
    if (r == NULL) {
        return;
    }

    distance += 10;

    avl_traversal_custom(r->right, distance);

    printf("\n");
    for (int i = 10; i < distance; i++) {
        printf(" ");
    }
    printf("%d\n", r->key);

    avl_traversal_custom(r->left, distance);
}

void avl_traversal_custom_wrapper(struct avl *t) {
    avl_traversal_custom(t->root, PRINT_DISTANCE);
}

void main_menu() {
    printf("1. Wyszukiwanie węzła\n");
    printf("2. Dodawanie węzła\n");
    printf("3. Usuwanie węzła\n");
    printf("4. Usuwanie danych z całego drzewa\n");
    printf("5. VLR\n");
    printf("6. LVR\n");
    printf("7. LRV\n");
    printf("8. Custom\n");
    printf("9. Zakończ\n");
}