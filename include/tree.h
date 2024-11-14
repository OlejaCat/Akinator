#ifndef DESICION_TREE_H
#define DESICION_TREE_H

typedef int tree_node_type;

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

Tree* treeCtor_(DUMP_PARAMETERS);
void treeDtor_(Tree* tree LOGGER_PARAMETERS);
void treeAddNode_(Tree* tree, tree_node_type data LOGGER_PARAMETERS);

#if defined(_DUMP) || defined(_LOGGER)
    #define treeCtor() treeCtor_(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#else
    #define treeCtor() treeCtor_()
#endif

#ifdef _LOGGER
    #define treeAddNode(tree_, data_) treeAddNode_(tree_, data_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeDtor(tree_) treeDtor_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#else
    #define treeAddNode(tree_, data_) treeAddNode_(tree_, data_)
    #define treeDtor(tree_) treeDtor_(tree_)
#endif

#endif // DESICION_TREE_H
