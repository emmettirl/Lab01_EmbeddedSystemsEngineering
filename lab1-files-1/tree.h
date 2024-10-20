#ifndef LAB01_EMBDEDDEDSYSTEMSENGINEERING_TREE_H
#define LAB01_EMBDEDDEDSYSTEMSENGINEERING_TREE_H

#include "id.h"

struct Node {
    struct id_struct data;
    struct Node *ltree;
    struct Node *rtree;
};

struct Node* insert(struct Node* tree, struct id_struct p);
void inorder(struct Node* tree);

#endif //LAB01_EMBDEDDEDSYSTEMSENGINEERING_TREE_H
