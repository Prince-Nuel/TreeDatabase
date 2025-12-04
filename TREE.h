#ifndef TREE
#define TREE
#include "TREE.c"

struct tree *FREE(struct tree *root);                                // free all nodes
void view(struct tree *root);                                        // veiw all nodes
struct tree *rotate_left(struct tree *parent);                       // takes and address and rotate it in the left direction and bring back the new
struct tree *rotate_right(struct tree *parent);                      // takes and address and rotate it in the right direction and bring back the new
struct tree *search(int a, struct tree *root, struct tree **parent); // first value is what to search, second is the address of that searched, third modifies to the parent address
struct tree *create();

#endif