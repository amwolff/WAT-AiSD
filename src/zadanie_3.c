#include <stdio.h>
#include <stdlib.h>

// TODO(amwolff): set key, data, NULLs at make's
// TODO(amwolff): set NULLs after delete and after clear
// TODO(amwolff): handle errors in main()

struct bst_node {
    int key, data;
    struct bst_node *parent, *left, *right;
};

struct bst_node *make_bst_node(int key, int data);

struct bst {
    struct bst_node *root;
};

struct bst *make_bst();

struct bst_node *bst_search(struct bst *t, int key);

int bst_insert_node(struct bst *t, struct bst_node *n);

struct bst_node *bst_search_min_key(struct bst_node *n);

struct bst_node *bst_find_successor(struct bst_node *n);

int bst_delete_node(struct bst *t, int key);

void m461cfunc(struct bst_node *n);

void bst_clear(struct bst *t);

void bst_traversal_NLR(struct bst_node *n);

void bst_traversal_LNR(struct bst_node *n);

void bst_traversal_LRN(struct bst_node *n);

void main_menu();

int main() {
    struct bst *t = make_bst();

    main_menu();

    struct bst_node *n;
    int input = '\0';
    while (input != 'q') {
        input = getchar();
        switch (input) {
            case '1':
                bst_search(t, 0); // TODO(amwolff): make input available
                // TODO(amwolff): handle output
                break;
            case '2':
                // TODO(amwolff): make input available
                n = make_bst_node(0, 0);
                bst_insert_node(t, n);
                break;
            case '3':
                bst_delete_node(t, 0); // TODO(amwolff): make input available
                break;
            case '4':
                bst_clear(t);
            case '5':
                bst_traversal_NLR(t->root);
                break;
            case '6':
                bst_traversal_LNR(t->root);
                break;
            case '7':
                bst_traversal_LRN(t->root);
            default:
                break;
        }
    }

    free(t);
    return 0;
}

struct bst_node *make_bst_node(int key, int data) {
    struct bst_node *n = malloc(sizeof(struct bst_node));
    if (n == NULL) {
        return n;
    }
    n->key = key;
    n->data = data;
    return n;
}

struct bst *make_bst() {
    struct bst *t = malloc(sizeof(struct bst));
    if (t == NULL) {
        return t;
    }
    return t;
}

struct bst_node *bst_search(struct bst *t, int key) {
    struct bst_node *n = t->root;
    while (n != NULL && n->key != key) {
        if (key < n->key) {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    return n;
}

int bst_insert_node(struct bst *t, struct bst_node *n) {
    struct bst_node *y = NULL;
    struct bst_node *x = t->root;
    while (x != NULL) {
        if (n->key == x->key) {
            // update?
            // copy necessary data from n to x;
            // return 0;
            return 1;
        }

        y = x;
        if (n->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    n->parent = y;

    if (y == NULL) { // the tree is empty
        t->root = n;
        return 0;
    }

    if (n->key < y->key) {
        y->left = n;
    } else {
        y->right = n;
    }
}

struct bst_node *bst_search_min_key(struct bst_node *n) {
    while (n->left != NULL) {
        n = n->left;
    }
    return n;
}

struct bst_node *bst_find_successor(struct bst_node *n) {
    if (n->right != NULL) {
        return bst_search_min_key(n->right);
    }
    struct bst_node *x = n->parent;
    while (x != NULL && x->left != n) {
        n = x;
        x = x->parent;
    }
    return x;
}

int bst_delete_node(struct bst *t, int key) {
    struct bst_node *n = t->root;
    while (n != NULL) {
        if (key == n->key) {
            break;
        }
        if (key < n->key) {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    if (n == NULL) {
        return 1;
    }

    struct bst_node *y;
    if (n->left == NULL || n->right == NULL) {
        y = n;
    } else {
        y = bst_find_successor(n);
    }

    struct bst_node *x;
    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }

    if (x != NULL) {
        x->parent = y->parent;
    }

    if (y->parent == NULL) {
        t->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != n) {
        n->key = y->key;
        n->data = y->data;
    }

    free(y);
    return 0;
}

void m461cfunc(struct bst_node *n) {
    if (n == NULL) {
        return;
    }
    m461cfunc(n->left);
    m461cfunc(n->right);
    free(n);
}

void bst_clear(struct bst *t) {
    struct bst_node *r = t->root;
    m461cfunc(r);
}

void bst_traversal_NLR(struct bst_node *n) {
    if (n == NULL) {
        return;
    }
    printf("%d\n", n->key);
    bst_traversal_NLR(n->left);
    bst_traversal_NLR(n->right);
}

void bst_traversal_LNR(struct bst_node *n) {
    if (n == NULL) {
        return;
    }
    bst_traversal_LNR(n->left);
    printf("%d\n", n->key);
    bst_traversal_LNR(n->right);
}

void bst_traversal_LRN(struct bst_node *n) {
    if (n == NULL) {
        return;
    }
    bst_traversal_LRN(n->left);
    bst_traversal_LRN(n->right);
    printf("%d\n", n->key);
}

void main_menu() {
    printf("1. Wyszukiwanie węzła\n");
    printf("2. Dodawanie węzła\n");
    printf("3. Usuwanie węzła\n");
    printf("4. Usuwanie danych z całego drzewa\n");
    printf("5. VLR\n");
    printf("6. LVR\n");
    printf("7. LRV\n");
}