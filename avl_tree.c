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

int insert(t_tree *tree, int item) {
    t_node *node = create_node(item);

    if (node == NULL) {
        return 0;
    }

    t_node *new_root = recursive_insert(tree->root, node);

    if (new_root == NULL) {
        return 0;
    }

    tree->root = new_root;

    return 1;
}

static t_node* recursive_remove(t_node *node, t_node *node_to_remove) {
    if (node == NULL) {
        return NULL;
    }

    if (node->item == node_to_remove->item) {
        if (node->right == NULL && node->left == NULL) {
            free(node);
            return NULL;
        } else if (node->right == NULL && node->left != NULL) {
            t_node *left = node->left;

            free(node);

            return left;
        } else if (node->right != NULL && node->left == NULL) {
            t_node *right = node->right;

            free(node);

            return right;
        } else {
            t_node **aux = &(node->left);

            while ((*aux)->right != NULL) {
                aux = &((*aux)->right);
            }

            t_node *biggest_left = *aux;
            *aux = biggest_left->left;

            node->item = biggest_left->item;

            free(biggest_left);

            return node;
        }
    } else if (node_to_remove->item < node->item) {
        node->left = recursive_remove(node->left, node_to_remove);
    } else {
        node->right = recursive_remove(node->right, node_to_remove);
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = get_balance(node);

    if (balance > 1) {
        int right_balance = get_balance(node->right);
        if (right_balance > 0) {
            node = rotate_left(node);
        } else {
            node = rotate_right_left(node);
        }
    } else if (balance < -1) {
        int left_balance = get_balance(node->left);
        if (left_balance < 0) {
            node = rotate_right(node);
        } else {
            node = rotate_left_right(node);
        }
    }

    return node;
}

static int total_nodes_recursive(t_node *node){
    if (node == NULL) {
        return 0;
    }

    return 1 + total_nodes_recursive(node->left) + total_nodes_recursive(node->right);
}

int remove(t_tree *tree, int item) {
    if (is_empty(tree)) {
        return 0;
    }

    t_node *node_to_remove = search(tree, item);

    if (node_to_remove == NULL) {
        return 0;
    }

    tree->root = recursive_remove(tree->root, node_to_remove);

    return 1;
}

int total_nodes(t_tree* tree) {
    if (is_empty(tree)) {
        return 0;
    }

    return total_nodes_recursive(tree->root);
}

t_node* search(t_tree *tree, int item) {
    if (is_empty(tree)) {
        return NULL;
    }

    t_node *aux = tree->root;

    while (aux != NULL && aux->item != item) {
        if (item < aux->item) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    return aux;
}

void pre_order(t_node *node) {
    if (node == NULL) {
        return;
    }

    printf("%d\t", node->item);
    pre_order(node->left);
    pre_order(node->right);
}

void in_order(t_node *node) {
    if (node == NULL) {
        return;
    }

    in_order(node->left);
    printf("%d\t", node->item);
    in_order(node->right);
}

void post_order(t_node *node) {
    if (node == NULL) {
        return;
    }

    post_order(node->left);
    post_order(node->right);
    printf("%d\t", node->item);
}

void width_traversal(t_tree *tree) {
    if (is_empty(tree)) {
        return;
    }

    int tree_size = total_nodes(tree->root);
    int queue_size = (tree_size + 1) / 2;
    t_node **queue = malloc(sizeof(t_node*) * queue_size);

    if (queue == NULL) {
        return;
    }

    int start = 0;
    int end = 0;

    queue[end] = tree->root;

    for (int i = 0; i < tree_size; i++) {
        t_node *current = queue[start];
        start = (start + 1) % queue_size;

        printf("%d\t", current->item);

        if (current->left != NULL) {
            end = (end + 1) % queue_size;
            queue[end] = current->left;
        }

        if (current->right != NULL) {
            end = (end + 1) % queue_size;
            queue[end++] = current->right;
        }
    }

    free(queue);
}
