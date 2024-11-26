#ifndef DESICION_TREE_H
#define DESICION_TREE_H

#include <stdlib.h>
#include <stdbool.h>

typedef char* tree_node_type;

typedef struct Tree Tree;

#if defined(_DUMP) || defined(_LOGGER)
    #define DUMP_PARAMETERS const char* file_name, int line_number, const char* function
#else
    #define DUMP_PARAMETERS
#endif

#ifdef _LOGGER
    #define LOGGER_PARAMETERS , const char* file_name, int line_number, const char* function
#else
    #define LOGGER_PARAMETERS
#endif

typedef enum MoveState
{
    MoveState_STAYED_INPLACE = -1,
    MoveState_MOVED_TO_NEXT  =  0,
    MoveState_EMPTY_NODE     =  1,
} MoveState;

typedef enum OnWhatBranch
{
    OnWhatBranch_NONE  = 0,
    OnWhatBranch_LEFT  = 1,
    OnWhatBranch_RIGHT = 2,
} OnWhatBranch;


typedef struct DataOfNode
{
    int            depth;
    tree_node_type data;
    bool           is_end;
    OnWhatBranch   parent_branch;
} DataOfNode;

Tree* treeCtor_(DUMP_PARAMETERS);
void treeDtor_(Tree* tree LOGGER_PARAMETERS);
void treeAddNodeBinary_(Tree* tree, tree_node_type data LOGGER_PARAMETERS);
void treeInsertOnLeft_(Tree* tree, tree_node_type data LOGGER_PARAMETERS);
void treeInsertOnRight_(Tree* tree, tree_node_type data LOGGER_PARAMETERS);
MoveState treeMoveToLeftNode_(Tree* tree LOGGER_PARAMETERS);
MoveState treeMoveToRightNode_(Tree* tree LOGGER_PARAMETERS);
tree_node_type treeGetCurrentNodeData_(Tree* tree LOGGER_PARAMETERS);
void treeBackToParentNode_(Tree* tree LOGGER_PARAMETERS);
void treeBackToTop_(Tree* tree LOGGER_PARAMETERS);
bool treeIsNodeEnd_(Tree* tree LOGGER_PARAMETERS);
void treeInsertOnTopLeft_(Tree* tree, tree_node_type data LOGGER_PARAMETERS);
void treeInsertOnTopRight_(Tree* tree, tree_node_type data LOGGER_PARAMETERS);
DataOfNode* treePreOrderTravers(Tree* tree);
size_t treeNodesQuantity(Tree* tree);
DataOfNode* treeGetPathToNode(Tree* tree, tree_node_type node);

#if defined(_DUMP) || defined(_LOGGER)
    #define treeCtor() treeCtor_(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#else
    #define treeCtor() treeCtor_()
#endif

#ifdef _LOGGER
    #define treeAddNodeBinary(tree_, data_) treeAddNodeBinary_(tree_, data_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeInsertOnLeft(tree_, data_ ) treeInsertOnLeft_(tree_, data_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeInsertOnRight(tree_, data_ ) treeInsertOnRight_(tree_, data_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeMoveToLeftNode(tree_) treeMoveToLeftNode_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeMoveToRightNode(tree_) treeMoveToRightNode_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeGetCurrentNodeData(tree_) treeGetCurrentNodeData_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeIsNodeEnd(tree_) treeIsNodeEnd_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeDtor(tree_) treeDtor_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeInsertOnTopLeft(tree_, data_) treeInsertOnTopLeft_(tree_, data_, \
                                                                   __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeInsertOnTopRight(tree_, data_) treeInsertOnTopRight_(tree_, data_, \
                                                                     __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeBackToParentNode(tree_) treeBackToParentNode_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeBackToTop(tree_) treeBackToTop_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#else
    #define treeAddNodeBinary(tree_, data_) treeAddNodeBinary_(tree_, data_)
    #define treeInsertOnLeft(tree_, data_ ) treeInsertOnLeft_(tree_, data_)
    #define treeInsertOnRight(tree_, data_ ) treeInsertOnRight_(tree_, data_)
    #define treeMoveToLeftNode(tree_) treeMoveToLeftNode_(tree_)
    #define treeMoveToRightNode(tree_) treeMoveToRightNode_(tree_)
    #define treeGetCurrentNodeData(tree_) treeGetCurrentNodeData_(tree_)
    #define treeIsNodeEnd(tree_) treeIsNodeEnd_(tree_)
    #define treeDtor(tree_) treeDtor_(tree_)
    #define treeInsertOnTopLeft(tree_, data_) treeInsertOnTopLeft_(tree_, data_);
    #define treeInsertOnTopRight(tree_, data_) treeInsertOnTopRight_(tree_, data_);
    #define treeBackToParentNode(tree_) treeBackToParentNode_(tree_);
    #define treeBackToTop(tree_) treeBackToTop_(tree_)
#endif

#endif // DESICION_TREE_H
