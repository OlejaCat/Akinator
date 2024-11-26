#include <stdio.h>
#include <stdlib.h>

#include "akinator_logic.h"
#include "akinator_files_work.h"
#include "tree.h"

int main()
{
    Akinator akinator = {.akinator_tree = treeCtor()};

    akinatorReadDataBaseFromJSON(&akinator, "data_bases/wtf.json");

        akinatorQuess(&akinator);

        // treeBackToTop(akinator.akinator_tree);
//
//     DataOfNode* tree_information = treePreOrderTravers(akinator.akinator_tree);
//
//     printf("\n");
//     for (size_t i = 0; i < 9; i++)
//     {
//         printf("depth: %lu, data: %s, is end: %d\n", tree_information[i].depth,
//                                                      tree_information[i].data,
//                                                      tree_information[i].is_end);
//     }
//
//     free(tree_information);

    akinatorSaveDataBaseToJSON(&akinator, "data_bases/wtf.json");

    treeDtor(akinator.akinator_tree);

    return 0;
}
