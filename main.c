#include<stdio.h>
#include"avl_tree.h"

void menu() {
    printf("-----------------------------------------------\n");
    printf("Select a function:\n");
    printf(" 1 - insert\n");
    printf(" 2 - height\n");
    printf(" 3 - total_nodes\n");
    printf(" 4 - search\n");
    printf(" 5 - remove\n");
    printf(" 6 - is_empty\n");
    printf(" 7 - pre_order\n");
    printf(" 8 - in_order\n");
    printf(" 9 - post_order\n");
    printf("10 - width_traversal\n");
    printf("11 - exit\n");
    printf("-----------------------------------------------\n");
    printf("Your choice: ");
}

int main(){
    t_tree *tree = create_tree();

    if (tree == NULL) {
        printf("Failed to create the tree\nAborting...\n");
        return 1;
    }

    int opt = 0;
    do {
        menu();
        scanf("%d", &opt);

        switch (opt) {
            case 1: {
                printf("-----------------------------------------------\n");

                int item;

                printf("Enter the value to be inserted: ");
                scanf("%d", &item); 
                
                int insert_status = insert(tree, item);

                if (insert_status) {
                    printf("\n%d inserted successfully\n");
                } else {
                    printf("\nFailed to insert\n");
                }

                break;
            }
            case 2:
                printf("-----------------------------------------------\n");
                printf("Tree height: %d\n", height(tree));

                break;
            case 3:
                printf("-----------------------------------------------\n");
                printf("Total number of nodes in the tree: %d\n", total_nodes(tree));

                break;
            case 4: {
                printf("-----------------------------------------------\n");

                int item;

                printf("Insert the value of the node you want\nto search for: ");
                scanf("%d", &item);

                t_node *node = search(tree->root, item);

                if (node != NULL) {
                    printf("\nNode:\n");
                    printf("\t%d\n", node->item);
                    if (node->left == NULL) {
                        printf("NULL\t\t");
                    } else {
                        printf("%d\t\t", node->left->item);
                    }

                    if (node->right == NULL) {
                        printf("NULL\n");
                    } else {
                        printf("%d\n", node->right->item);
                    }
                } else {
                    printf("\n%d IS NOT in the tree\n", item);
                }

                break;
            }
            default:
                break;
        }
    } while (opt != 11);

    destroy_tree(tree);

    return 0;
}
