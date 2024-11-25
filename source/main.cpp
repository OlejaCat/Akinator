#include <stdio.h>
#include <stdlib.h>

#include "akinator_logic.h"
#include "tree.h"

int main()
{
    Akinator akinator = {.akinator_tree = treeCtor()};

    while (true)
    {
        akinatorQuess(&akinator);

        treeBackToTop(akinator.akinator_tree);
    }
    treeDtor(akinator.akinator_tree);

    return 0;
}
