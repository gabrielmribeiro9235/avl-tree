#include<stdio.h>
#include<stdlib.h>
#include"avl_tree.h"

t_tree* create_tree() {
    t_tree *tree = malloc(sizeof(t_tree));

    if (tree == NULL) {
        return NULL;
    }

    tree->root = NULL;

    return tree;
}

t_node* create_node(int item) {
    t_node *node = malloc(sizeof(t_node));

    if (node == NULL) {
        return NULL;
    }

    node->item = item;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static void recursive_destroy_tree(t_node *root) {
    if (root == NULL) {
        return;
    }

    recursive_destroy_tree(root->left);
    recursive_destroy_tree(root->right);
    free(root);
}

void destroy_tree(t_tree *tree) {
    if (tree == NULL) {
        return;
    }

    recursive_destroy_tree(tree->root);
    free(tree);
}

int is_empty(t_tree *tree) {
    return tree == NULL || tree->root == NULL;
}

int height(t_node *node) {
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

static int get_balance(t_node *node) {
    return height(node->right) - height(node->left);
}

static t_node *rotate_left(t_node *node) {
    t_node *right = node->right;

    node->right = right->left;
    right->left = node;

    return right;
}

static t_node *rotate_right(t_node *node) {
    t_node *left = node->left;

    node->left = left->right;
    left->right = node;

    return left;
}

static t_node *rotate_right_left(t_node *node) {
    t_node *right = node->right;

    node->right = right->left;
    right->left = node->right->right;
    node->right->right = right;

    return rotate_left(node);
}

static t_node *rotate_left_right(t_node *node) {
    t_node *left = node->left;

    node->left = left->right;
    left->right = node->left->left;
    node->left->left = left;

    return rotate_right(node);
}

static int max(int a, int b) {
    return a > b ? a : b;
}

static t_node* recursive_insert(t_node *root, t_node *new_node) {
    if (root == NULL) {
        root = new_node;
        new_node->height++;
        return root;
    }

    if (root->item == new_node->item) {
        return NULL;
    } else if (new_node->item < root->item) {
        t_node *left = recursive_insert(root->left, new_node);

        if (left == NULL) {
            return NULL;
        }

        root->left = left;
    } else {
        t_node *right = recursive_insert(root->right, new_node);

        if (right == NULL) {
            return NULL;
        }

        root->right = right;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = get_balance(root);

    if (balance > 1) {
        int right_balance = get_balance(root->right);
        if (right_balance > 0) {
            root = rotate_left(root);
        } else {
            root = rotate_right_left(root);
        }
    } else if (balance < -1) {
        int left_balance = get_balance(root->left);
        if (left_balance < 0) {
            root = rotate_right(root);
        } else {
            root = rotate_left_right(root);
        }
    }

    return root;
}
