#include "tree.h"

int main()
{
    Tree* tree = treeCtor();

    treeAddNode(tree, 10);
    treeAddNode(tree, 20);
    treeAddNode(tree, 5);
    treeAddNode(tree, 2);

    treeDtor(tree);

    return 0;
}
