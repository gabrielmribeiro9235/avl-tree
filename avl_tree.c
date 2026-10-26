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

static int recursive_insert(t_node *root, t_node *new_node) {
    if (root->item == new_node->item) {
        return 0;
    }

    if (root == NULL) {
        root = new_node;
        new_node->height++;
        return 1;
    }

    if (new_node->item < root->item) {
        return recursive_insert(root->left, new_node);
    }

    return recursive_insert(root->right, new_node);
}
