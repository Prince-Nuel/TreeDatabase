#include <stdio.h>
#include <stdlib.h>
#include "TREE.h"

typedef struct tree RB;

enum color
{
    db = -1,
    black = 0,
    red = 1
};
enum dir
{
    left,
    right
};
RB *bal_red(RB **);
void insert_RB(RB *r, RB **);
void recolor(RB **root, int, int);
int check_red(RB *root);
RB *bal_db(int a, RB **);
void delete_RB(int a);
int check_db(RB *parent);
void swap(int L, int R, RB **parent, RB **sibling);

RB *ROOT = NULL;
RB *Red_Black = NULL;

int main()
{
    int x = 0;
    printf("select the operation\n");
    printf("(1)create data (2)insert data (3)delete data (4)view data (5)search data (6)get root (0)Exit\n");
    while (1)
    {
        if (scanf("%d", &x) == 1)
            break;
        printf("INVALID INPUT!! select the operation\n");
        while (getchar() != '\n')
            ;
    }
    while (x)
    {
        switch (x)
        {
        case 1:
            FREE(ROOT);
            FREE(Red_Black);
            ROOT = Red_Black = NULL;

            ROOT = create();
            insert_RB(ROOT, &Red_Black);
            FREE(ROOT);
            ROOT = NULL;
            break;
        case 2:
            if (Red_Black == NULL)
                printf("NO DATA CREATED YET!!\n");
            else
            {
                ROOT = malloc(sizeof(RB));
                ROOT->left = ROOT->right = NULL;
                printf("Enter data:\n");
                while (1)
                {
                    if (scanf("%d", &ROOT->data) == 1)
                        break;
                    printf("INVALID INPUT!! select the operation\n");
                    while (getchar() != '\n')
                        ;
                }
                insert_RB(ROOT, &Red_Black);
                FREE(ROOT);
                ROOT = NULL;
                printf("INSERTED!!!\n");
            }
            break;
        case 3:
            if (Red_Black == NULL)
                printf("NO DATA CREATED YET!!\n");
            else
            {
                int a = 0;
                printf("select the data you want to delete\n");
                view(Red_Black);
                while (1)
                {
                    if (scanf("%d", &a) == 1)
                        break;
                    printf("INVALID INPUT!! select the operation\n");
                    while (getchar() != '\n')
                        ;
                }
                delete_RB(a);
                printf("DELETED!!!!\n");
            }
            break;
        case 4:
            if (Red_Black == NULL)
                printf("NO DATA CREATED YET!!\n");
            else
                view(Red_Black);
            break;
        case 5:
            if (Red_Black == NULL)
                printf("NO DATA CREATED YET!!\n");
            int a = 0;
            printf("Enter the data:\n");
            while (1)
            {
                if (scanf("%d", &a) == 1)
                    break;
                printf("INVALID INPUT!! select the operation\n");
                while (getchar() != '\n')
                    ;
            };
            RB *parent = NULL;
            if (search(a, Red_Black, &parent) != NULL)
                printf("VALUE EXIST!!\n");
            else
                printf("NOT FOUND!!\n");
            break;
        case 6:
            if (Red_Black == NULL)
                printf("NO DATA CREATED YET!!\n");
            printf("the root is = %d", Red_Black->data);
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
        }
    }
    FREE(Red_Black);
    return 0;
}

void recolor(RB **root, int dir, int color)
{
    RB *temp;
    temp = *root;
    if (temp == ROOT)
    {
        temp->color = black;
    }
    else
        temp->color = (temp->color == red) ? black : red;
    if (dir == left)
    {
        switch (color) // if the color is red it affects both siblings else just the right
        {
        case red:
            temp->left->color = (temp->left->color == red) ? black : red;
        case black:
            temp->right->color = (temp->right->color == red) ? black : red;
            break;
        }
    }
    if (dir == right)
    {
        switch (color) // if the color is red it affects both siblings else just the left
        {
        case red:
            temp->right->color = (temp->right->color == red) ? black : red;
        case black:
            temp->left->color = (temp->left->color == red) ? black : red;
            break;
        }
    }
}
RB *bal_red(RB **root)
{
    RB *temp;
    temp = *root;
    int L = check_red(temp->left);
    int R = check_red(temp->right);
    if (L == -1) // the red conflict is from left side
    {
        switch (R)
        {
        case black:
            temp = rotate_right(temp);
        case red:
            recolor(&temp, left, R); // tells recolor the direction of rc and color of it sibling node
            break;
        }
    }
    else if (R == -1) // the red conflict is from right side
    {
        switch (L)
        {
        case black:
            temp = rotate_left(temp);
        case red:
            recolor(&temp, right, L); // tells recolor the direction of rc and color of it sibling node
            break;
        }
    }
    else
        ;
    return temp;
}
int check_red(RB *root)
{
    if (root == NULL)
        return black;
    int L = check_red(root->left);
    int R = check_red(root->right);

    if ((red == root->color) && (red == L || red == R))
        return -1;

    return root->color;
}
void insert_RB(RB *r, RB **root)
{
    if (r == NULL)
        return;
    insert_RB(r->left, root);
    insert_RB(r->right, root);

    RB *temp, *new;
    temp = *root;
    new = malloc(sizeof(RB));
    new->left = new->right = NULL;
    new->color = red;

    if (*root == NULL)
    {
        *root = new;
        (*root)->data = r->data;
        (*root)->color = black;
        return;
    }
    else
    {
        while (1)
        {
            if (r->data > temp->data)
            {
                if (temp->right == NULL)
                {
                    temp->right = new;
                    temp->right->data = r->data;
                    break;
                }
                temp = temp->right;
            }
            else if (r->data < temp->data)
            {
                if (temp->left == NULL)
                {
                    temp->left = new;
                    temp->left->data = r->data;
                    break;
                }
                temp = temp->left;
            }
            else
                break;
        }
    }
    *root = bal_red(root);
}
void delete_RB(int a)
{
    RB *parent, *target, *succ;
    parent = target = NULL;
    parent = Red_Black;
    target = search(a, Red_Black, &parent);
    if (target == NULL)
    {
        printf("DOESN'T EXIST!!\n");
    }

    while (1)
    {
        succ = target;

        if (target->left == NULL && target->right == NULL)
        {
            if (target == Red_Black)
            {
                free(Red_Black);
                Red_Black = NULL;
                return;
            }
            else if (target->color == red)
            {
                if (parent->left == target)
                    parent->left = NULL;
                else if (parent->right == target)
                    parent->right = NULL;
                free(target);
                return;
            }
            else
            {
                target->color = db;
                break;
            }
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
        }
        succ->data = target->data;
    }
    Red_Black = bal_db(a, &Red_Black);
}
RB *bal_db(int a, RB **root)
{
    int L, R;
    RB *temp, *target;
    temp = *root;
    if (temp->data == a || temp == NULL)
        return temp;
    else if (a > temp->data)
        temp->right = bal_db(a, &temp->right);
    else
        temp->left = bal_db(a, &temp->left);

    if (check_db(temp->left) == db)
    {
        if (temp->left->data == a)
        {
            target = temp->left;
            temp->left = NULL;
            free(target);
        }
        if (temp->right == NULL)
        {
            temp->color = temp->color + db;
            return temp;
        }

        R = check_db(temp->right->left);
        L = check_db(temp->right->right);
        switch (check_db(temp->right))
        {
        case black:
            swap(L, R, &temp, &temp->right);
            temp = rotate_left(temp);
            temp->right->color = temp->right->color + db;
            break;

        case red:
            swap(L, R, &temp, &temp->right);
            temp = rotate_left(temp);
            temp->left->color = temp->left->color + db;
            break;
        }
    }

    else if (check_db(temp->right) == db)
    {
        if (temp->right->data == a)
        {
            target = temp->right;
            temp->right = NULL;
            free(target);
        }
        if (temp->left == NULL)
        {
            temp->color = temp->color + db;
            return temp;
        }
        R = check_db(temp->left->right);
        L = check_db(temp->left->left);
        switch (check_db(temp->left))
        {
        case black:
            swap(L, R, &temp, &temp->left);
            temp = rotate_right(temp);
            temp->left->color = temp->left->color + db;
            break;

        case red:
            swap(L, R, &temp, &temp->left);
            temp = rotate_right(temp);
            temp->right->color = temp->right->color + db;
            break;
        }
    }
    return temp;
}
int check_db(RB *parent)
{
    return (parent == NULL) ? black : parent->color;
}
void swap(int L, int R, RB **parent, RB **sibling)
{
    int c;
    RB *s, *p;
    s = *sibling;
    p = *parent;
    switch (s->color)
    {
    case black:
        if (L == black && R == black)
        {
            p->color = p->color + db;
            s->color = red;
        }
        else if (R == red && L == black)
        {
            s->color = red;
            if (check_db(s->left) == R)
            {
                s->left->color = L;
                s = rotate_right(s);
            }
            else if (check_db(s->right) == R)
            {
                s->right->color = L;
                s = rotate_left(s);
            }
            c = s->color;
            s->color = p->color;
            p->color = c;
        }
        else
        {
            c = s->color;
            s->color = p->color;
            p->color = c;
        }
        break;
    case red:
        s->color = black;
        p->color = red;
        break;
    }
}