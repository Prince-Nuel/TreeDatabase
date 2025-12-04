#include <stdio.h>
#include "TREE.h"

struct tree
{
    int color;
    int data;
    struct tree *left;
    struct tree *right;
};

struct tree *create()
{
    struct tree *new;
    int x = 0;
    new = malloc(sizeof(struct tree));
    new->left = new->right = NULL;
    printf("Enter data and zero(0) to exit:\n");
    while (1)
    {
        if (scanf("%d", &x) == 1)
            break;
        printf("select the operation\n");
        while (getchar() != '\n')
            ;
    }
    if (x == 0)
    {
        free(new);
        return NULL;
    }
    else
        new->data = x;
    printf("Enter left value of %d\n", x);
    new->left = create();
    printf("Enter right value of %d\n", x);
    new->right = create();

    return new;
}

struct tree *search(int a, struct tree *root, struct tree **parent)
{
    struct tree *temp;
    temp = root;
    while (temp != NULL)
    {
        if (temp->data == a)
        {
            return temp;
        }
        else if (a > temp->data)
        {
            *parent = temp;
            temp = temp->right;
        }
        else if (a < temp->data)
        {
            *parent = temp;
            temp = temp->left;
        }
    }
    return NULL;
}
struct tree *rotate_left(struct tree *parent)
{
    struct tree *child;
    child = parent->right;
    parent->right = child->left;
    child->left = parent;

    return child;
}
struct tree *rotate_right(struct tree *parent)
{
    struct tree *child;
    child = parent->left;
    parent->left = child->right;
    child->right = parent;

    return child;
}
struct tree *FREE(struct tree *root)
{
    if (root == NULL)
        return NULL;
    FREE((root)->left);
    FREE((root)->right);
    free(root);

    return NULL;
}
void view(struct tree *root)
{
    if (root == NULL)
        return;
    view(root->left);
    printf("%d ", root->data);
    view(root->right);
}
