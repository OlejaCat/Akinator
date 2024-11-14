#ifndef TREE_NODE_STRUCTURE_H
#define TREE_NODE_STRUCTURE_H

#include <stdlib.h>

#include "tree.h"

typedef struct TreeNode
{
    tree_node_type data;

    TreeNode*      left_node;
    TreeNode*      right_node;
    TreeNode*      parent_node;

    size_t         node_index;
} TreeNode;

typedef struct Tree
{
    TreeNode*   start_node;

    size_t      nodes_number;

#if defined(_LOGGER) || defined(_DUMP)
    const char* file;
    int         line;
    const char* function;
#endif
} Tree;

#endif // TREE_NODE_STRUCTURE_H
