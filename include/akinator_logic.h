#ifndef AKINATOR_LOGIC_H
#define AKINATOR_LOGIC_H

#include "tree.h"

typedef struct Akinator
{
    Tree* akinator_tree;
} Akinator;

void akinatorQuess(Akinator* akinator);

#endif // AKINATOR_LOGIC_H
