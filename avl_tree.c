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
