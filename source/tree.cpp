#include "tree.h"

#include <assert.h>

#include "tree_node_structure.h"
#include "tree_dump.h"


// static --------------------------------------------------------------------------------------------------------------


static TreeNode* createNewNode(tree_node_type data, TreeNode* parent_node, size_t index);
static void recursiveDestructTree(TreeNode* node);

#define ASSERT_FOR_LOGGER_ assert(file_name != NULL); \
                           assert(function  != NULL);

#define PASTE_DATA_LOGGER_ tree->file     = file_name; \
                           tree->line     = line_number; \
                           tree->function = function;


// public --------------------------------------------------------------------------------------------------------------


// --------------------------------------- CONSTRUCTOR -----------------------------------------------------------------


Tree* treeCtor_(DUMP_PARAMETERS)
{
#if defined(_DUMP) || defined(_LOGGER)
    ASSERT_FOR_LOGGER_
#endif

    Tree* tree = (Tree*)calloc(1, sizeof(Tree));
    if (tree == NULL)
    {
        return NULL;
    }

    tree->start_node   = NULL;
    tree->current_node = NULL;
    tree->nodes_number = 0;

#if defined(_DUMP) || defined(_LOGGER)
    PASTE_DATA_LOGGER_
#endif

#ifdef _LOGGER
    treeOpenLogFile();
    treeLogState(tree);
#endif

    return tree;
}


// ------------------------------------------ RETURN INFORMATION -------------------------------------------------------


bool treeIsNodeEnd_(Tree* tree LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif

    TreeNode* node = tree->current_node;

    return node->left_node == NULL && node->right_node == NULL;
}


tree_node_type treeGetCurrentNodeData_(Tree* tree LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif

    if (tree->current_node == NULL)
    {
        return NULL;
    };

    return tree->current_node->data;
}


// ------------------------------------------ MOVE ---------------------------------------------------------------------


void treeBackToTop_(Tree* tree LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    tree->current_node = tree->start_node;

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif
}


void treeBackToParentNode_(Tree* tree LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    if (tree->current_node == NULL)
    {
        return;
    }

    if (tree->current_node->parent_node == NULL)
    {
        return;
    }

    tree->current_node = tree->current_node->parent_node;

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif
}



MoveState treeMoveToLeftNode_(Tree* tree LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    if (tree->current_node->left_node == NULL)
    {
        return MoveState_EMPTY_NODE;
    }

    tree->current_node = tree->current_node->left_node;

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif

    return MoveState_MOVED_TO_NEXT;
}


MoveState treeMoveToRightNode_(Tree* tree LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    if (tree->current_node->right_node == NULL)
    {
        return MoveState_EMPTY_NODE;
    }

    tree->current_node = tree->current_node->right_node;

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif

    return MoveState_MOVED_TO_NEXT;
}


// ------------------------------------------ ADD ----------------------------------------------------------------------


void treeInsertOnLeft_(Tree* tree, tree_node_type data LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    TreeNode* node = createNewNode(data, tree->current_node, tree->nodes_number);
    tree->nodes_number++;

    if (tree->current_node == NULL)
    {
        tree->start_node = node;
        tree->current_node = node;
        return;
    }

    if (tree->current_node->left_node != NULL)
    {
        TreeNode* left_node = tree->current_node->left_node;
        node->left_node = left_node;
    }

    tree->current_node->left_node = node;

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif
}


void treeInsertOnRight_(Tree* tree, tree_node_type data LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    TreeNode* node = createNewNode(data, tree->current_node, tree->nodes_number);
    tree->nodes_number++;

    if (tree->current_node == NULL)
    {
        tree->start_node = node;
        tree->current_node = node;
        return;
    }

    if (tree->current_node->left_node != NULL)
    {
        TreeNode* right_node = tree->current_node->right_node;
        node->right_node = right_node;
    }

    tree->current_node->right_node = node;

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif
}


void treeInsertOnTopLeft_(Tree* tree, tree_node_type data LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    if (tree->current_node->parent_node == NULL)
    {
        return;
    }

    TreeNode* node = createNewNode(data, tree->current_node->parent_node, tree->nodes_number);
    tree->nodes_number++;

    if (tree->current_node->parent_node->left_node == tree->current_node)
    {
        tree->current_node->parent_node->left_node = node;
    }
    else
    {
        tree->current_node->parent_node->right_node = node;
    }

    node->left_node = tree->current_node;
    tree->current_node->parent_node = node;

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif
}


void treeInsertOnTopRight_(Tree* tree, tree_node_type data LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    if (tree->current_node->parent_node == NULL)
    {
        return;
    }

    TreeNode* node = createNewNode(data, tree->current_node->parent_node, tree->nodes_number);
    tree->nodes_number++;

    if (tree->current_node->parent_node->left_node == tree->current_node)
    {
        tree->current_node->parent_node->left_node = node;
    }
    else
    {
        tree->current_node->parent_node->right_node = node;
    }

    node->right_node = tree->current_node;
    tree->current_node->parent_node = node;

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif
}


void treeAddNodeBinary_(Tree* tree, tree_node_type data LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    TreeNode* current_node = tree->current_node;
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
        tree->start_node   = new_node;
        tree->current_node = new_node;

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
    PASTE_DATA_LOGGER_

    treeLogState(tree);
#endif
}


// --------------------------------------- DESTRUCTOR -----------------------------------------------------------------


void treeDtor_(Tree* tree LOGGER_PARAMETERS)
{
    assert(tree != NULL);

#ifdef _LOGGER
    ASSERT_FOR_LOGGER_
#endif

    if (tree == NULL)
    {
        return;
    }

#ifdef _DUMP
    treeDumpToHtm(tree);
#endif

#ifdef _LOGGER
    PASTE_DATA_LOGGER_

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

    free(node->data);
    free(node);
}


#undef ASSERT_FOR_LOGGER_
#undef PASTE_DATA_LOGGER_
