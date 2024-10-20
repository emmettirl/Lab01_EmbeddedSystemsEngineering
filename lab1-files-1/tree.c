#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "id.h"

// I adapted this code to accept the struct id_struct which I made in id.h
// This allows the tree to store the id_struct and the line numbers it was found on in one place

struct Node* newTree(struct id_struct p) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = p;
    n->ltree = n->rtree = NULL;
    return n;
}

struct Node* insert(struct Node* tree, struct id_struct p) {
    if (tree == NULL)
        return newTree(p);
    int cmp = strcmp(p.identifier, tree->data.identifier);
    if (cmp <= 0)
        tree->ltree = insert(tree->ltree, p);
    else
        tree->rtree = insert(tree->rtree, p);
    return tree;
}

void inorder(struct Node* tree) {
    if (tree == NULL)
        return;
    inorder(tree->ltree);
    printf("%s: ", tree->data.identifier);
    for (int j = 0; j < tree->data.occurrenceCount; j++) {
        printf("%d ", tree->data.originalLineIndices[j]);
    }
    printf("\n");
    inorder(tree->rtree);
}
