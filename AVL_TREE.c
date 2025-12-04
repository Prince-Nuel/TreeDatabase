#include <stdio.h>
#include <stdlib.h>
#include "TREE.h"

enum direction
{
    right,
    left
};
struct tree *AVL_TREE;
struct tree *ROOT = NULL;
void insert(int a, struct tree **);
void delete(int a, struct tree **);
void insert_inorder(struct tree *, struct tree **);
struct tree *AVL();
struct tree *balance(struct tree **);
struct tree *Rotate(struct tree **Parent, int a);
int height(struct tree *);

int main()
{
    int x = 0;
    printf("select the operation\n");
    printf("(1)create data (2)insert data (3)delete data (4)view data (5)search data (6)get root (0)Exit\n");
    while (1)
    {
        if (scanf("%d", &x) == 1)
            break;
        printf("INVALID INPUT!!! select the operation\n");
        while (getchar() != '\n')
            ;
    }
    while (x)
    {
        switch (x)
        {
        case 1:
            FREE(ROOT);
            FREE(AVL_TREE);
            ROOT = AVL_TREE = NULL;

            ROOT = create();
            AVL_TREE = AVL();
            break;
        case 2:
            if (AVL_TREE == NULL)
                printf("NO DATA CREATED YET!!\n");
            else
            {
                int a;
                printf("Enter data:\n");
                while (1)
                {
                    if (scanf("%d", &a) == 1)
                        break;
                    printf("INVALID INPUT!!! select the operation\n");
                    while (getchar() != '\n')
                        ;
                }
                insert(a, &AVL_TREE);
                AVL_TREE = balance(&AVL_TREE);
            }
            break;
        case 3:
            if (AVL_TREE == NULL)
                printf("NO DATA CREATED YET!!\n");
            else
            {
                int a = 0;
                printf("select the data you want to delete\n");
                view(AVL_TREE);
                while (1)
                {
                    if (scanf("%d", &a) == 1)
                        break;
                    printf("INVALID INPUT!!! select the operation\n");
                    while (getchar() != '\n')
                        ;
                }
                delete(a, &AVL_TREE);
                AVL_TREE = balance(&AVL_TREE);
            }
            break;
        case 4:
            if (AVL_TREE == NULL)
                printf("NO DATA CREATED YET!!\n");
            else
                view(AVL_TREE);
            break;
        case 5:
            if (AVL_TREE == NULL)
                printf("NO DATA CREATED YET!!\n");
            int a = 0;
            printf("Enter the data:\n");
            while (1)
            {
                if (scanf("%d", &a) == 1)
                    break;
                printf("INVALID INPUT!!! select the operation\n");
                while (getchar() != '\n')
                    ;
            }
            struct tree *parent = NULL;
            if (search(a, AVL_TREE, &parent) != NULL)
                printf("VALUE EXIST!!\n");
            else
                printf("NOT FOUND!!\n");
            break;
        case 6:
            if (AVL_TREE == NULL)
                printf("NO DATA CREATED YET!!\n");
            printf("the root is = %d", AVL_TREE->data);
            break;
        default:
            printf("invaild input!!\n");
        }
        printf("\n(1)create data (2)insert data (3)delete data (4)veiw data (5)search data (6)get root (0)Exit\n");
        while (1)
        {
            if (scanf("%d", &x) == 1)
                break;
            printf("INVALID INPUT!!! select the operation\n");
            while (getchar() != '\n')
                ;
        };
    }
    FREE(ROOT);
    FREE(AVL_TREE);
    return 0;
}
struct tree *AVL()
{
    insert_inorder(ROOT, &AVL_TREE);
    AVL_TREE = balance(&AVL_TREE);

    return AVL_TREE;
}

struct tree *balance(struct tree **root)
{
    struct tree *branch;
    branch = *root;
    int L, R;
    L = R = 0;
    if (branch == NULL)
        return NULL;
    branch->left = balance(&branch->left);
    branch->right = balance(&branch->right);

    L = height(branch->left);
    R = height(branch->right);

    int diff = L - R;
    if (diff < -1)
        branch = Rotate(&branch, left);
    else if (diff > 1)
        branch = Rotate(&branch, right);
    else
        ;
    return branch;
}
struct tree *Rotate(struct tree **Parent, int a)
{
    struct tree *Gparent;
    Gparent = *Parent;
    if (a == right)
    {
        if (height(Gparent->left->right) > height(Gparent->left->left))
        {
            Gparent->left = rotate_left(Gparent->left);
            Gparent = rotate_right(Gparent);
        }
        else
            Gparent = rotate_right(Gparent);
    }
    else if (a == left)
    {
        if (height(Gparent->right->left) > height(Gparent->right->right))
        {
            Gparent->right = rotate_right(Gparent->right);
            Gparent = rotate_left(Gparent);
        }
        else
            Gparent = rotate_left(Gparent);
    }
    return Gparent;
}

// search

void insert_inorder(struct tree *src, struct tree **dest)
{
    if (src == NULL)
        return;
    insert_inorder(src->left, dest);
    insert(src->data, dest);
    insert_inorder(src->right, dest);
}
void insert(int a, struct tree **root)
{

    struct tree *new, *temp;
    new = malloc(sizeof(struct tree));
    new->left = new->right = NULL;

    temp = *root;
    if (*root == NULL)
    {
        *root = new;
        (*root)->data = a;
        return;
    }
    while (1)
    {
        if (a < temp->data)
        {
            if (temp->left == NULL)
            {
                temp->left = new;
                new->data = a;

                break;
            }
            temp = temp->left;
        }
        else if (a > temp->data)
        {
            if (temp->right == NULL)
            {
                temp->right = new;
                new->data = a;
                break;
            }
            temp = temp->right;
        }
        else
        {
            printf("already exist\n");
            free(new);
            return;
        }
    }
    printf("INSERTED!!\n");
    return;
}
void delete(int a, struct tree **root) // Deleting  only leaf nodes
{
    struct tree *target, *successor, *parent;
    parent = NULL;
    target = *root;
    target = search(a, target, &parent);
    successor = target;
    while (1)
    {

        if (target->right == NULL && target->left == NULL)
        {
            if (target == *root)
            {
                free(*root);
                *root = NULL;
                printf("DELETED!!\n");
                return;
            }
            if (parent != NULL)
            {
                if (parent->right == target)
                    parent->right = NULL;
                if (parent->left == target)
                    parent->left = NULL;
            }

            free(target);
            printf("DELETED!!\n");
            return;
        }
        else if (target->right != NULL)
        {
            parent = target;
            target = target->right;
            while (target->left != NULL)
            {
                parent = target;
                target = target->left;
            }
            successor->data = target->data;
            successor = target;
        }
        else
        {
            parent = target;
            target = target->left;
            while (target->right != NULL)
            {
                parent = target;
                target = target->right;
            }
            successor->data = target->data;
            successor = target;
        }
    }
}

int height(struct tree *root)
{
    if (root == NULL)
        return 0;
    int L = height(root->left);
    int R = height(root->right);

    return ((L >= R) ? L : R) + 1;
}
