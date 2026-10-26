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
