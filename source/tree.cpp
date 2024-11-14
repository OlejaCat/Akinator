#include "tree.h"

#include <assert.h>

#include "tree_node_structure.h"
#include "tree_dump.h"


// static --------------------------------------------------------------------------------------------------------------


static TreeNode* createNewNode(tree_node_type data, TreeNode* parent_node, size_t index);
static void recursiveDestructTree(TreeNode* node);


// public --------------------------------------------------------------------------------------------------------------


Tree* treeCtor_(DUMP_PARAMETERS)
{
#if defined(_DUMP) || defined(_LOGGER)
    assert(file_name != NULL);
    assert(function  != NULL);
#endif

    Tree* tree = (Tree*)calloc(1, sizeof(Tree));

    tree->start_node   = NULL;
    tree->nodes_number = 0;

#if defined(_DUMP) || defined(_LOGGER)
    tree->file     = file_name;
    tree->line     = line_number;
    tree->function = function;
#endif

#ifdef _LOGGER
    treeOpenLogFile();
    treeLogState(tree);
#endif

    return tree;
}


void treeAddNode_(Tree* tree, tree_node_type data LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    assert(file_name != NULL);
    assert(function  != NULL);
#endif

    TreeNode* current_node = tree->start_node;
    TreeNode* parent_node  = NULL;
    while (current_node != NULL)
    {
        parent_node = current_node;
        current_node = current_node->data <= data
                        ? current_node->right_node
                        : current_node->left_node;
    }

    TreeNode* new_node = createNewNode(data, parent_node, tree->nodes_number);
    tree->nodes_number++;

    if (parent_node == NULL)
    {
        tree->start_node = new_node;

        return;
    }

    if (parent_node->data > data)
    {
        parent_node->left_node = new_node;
    }
    else
    {
        parent_node->right_node = new_node;
    }

#ifdef _LOGGER
    tree->file     = file_name;
    tree->line     = line_number;
    tree->function = function;

    treeLogState(tree);
#endif
}


void treeDtor_(Tree* tree LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    assert(file_name != NULL);
    assert(function  != NULL);
#endif

    if (tree == NULL)
    {
        return;
    }

#ifdef _DUMP
    treeDumpToHtm(tree);
#endif

#ifdef _LOGGER
    tree->file     = file_name;
    tree->line     = line_number;
    tree->function = function;

    treeLogState(tree);
#endif

    recursiveDestructTree(tree->start_node);
    free(tree);
}


// static --------------------------------------------------------------------------------------------------------------


static TreeNode* createNewNode(tree_node_type data,
                               TreeNode*      parent_node,
                               size_t         index)
{
    TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));

    node->data        = data;
    node->parent_node = parent_node;
    node->left_node   = NULL;
    node->right_node  = NULL;

    node->node_index = index;

    return node;
}


static void recursiveDestructTree(TreeNode* node)
{
    if (node == NULL)
    {
        return;
    }

    recursiveDestructTree(node->left_node);
    recursiveDestructTree(node->right_node);

    free(node);
}

