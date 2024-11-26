#include <stdio.h>
#include <stdlib.h>

#include "akinator_logic.h"
#include "akinator_files_work.h"
#include "tree.h"

int main()
{
    Akinator akinator = {.akinator_tree = treeCtor()};

//     while (true)
//     {
//         akinatorQuess(&akinator);
//
//         treeBackToTop(akinator.akinator_tree);
//     }

    akinatorReadDataBaseFromFile(&akinator, "data_bases/test.json");

    treeDtor(akinator.akinator_tree);

    return 0;
}
