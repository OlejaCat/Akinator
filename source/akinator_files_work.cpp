#include "akinator_files_work.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "helpful_functions.h"
#include "tree.h"


// static --------------------------------------------------------------------------------------------------------------


static const size_t SIZE_OF_BUFFER = 128;


// public --------------------------------------------------------------------------------------------------------------


void akinatorReadDataBaseFromJSON(Akinator* akinator, const char* file_path)
{
    assert(akinator  != NULL);
    assert(file_path != NULL);

    FILE* input_file = fopen(file_path, "r");
    if (input_file == NULL)
    {
        fclose(input_file);
        return;
    }

    size_t size_of_file = getFileSize(input_file);

    char* data_file = (char*)calloc(size_of_file + 1, sizeof(char));
    if (data_file == NULL)
    {
        fclose(input_file);
        return;
    }

    size_t return_code = fread(data_file,
                               sizeof(data_file[0]),
                               size_of_file,
                               input_file);
    fclose(input_file);
    if (return_code != size_of_file)
    {
        free(data_file);
        return;
    }

    char* savetoken_1 = NULL;
    char* savetoken_2 = NULL;

    char* token = strtok_r(data_file, ",", &savetoken_1);
    char buffer_answer[SIZE_OF_BUFFER] = "да";
    while (token)
    {
        size_t number_of_close_bracket = 0;

        char* token_2 = strtok_r(token, ":", &savetoken_2);
        while (token_2)
        {
            char buffer[SIZE_OF_BUFFER] = {};
            sscanf(token_2, "%*[^\"] \"%63[^\"]", buffer);

            if (strcmp(buffer, "да")
             && strcmp(buffer, "нет"))
            {
                char* heap_buffer = (char*)calloc(strlen(buffer) + 1, sizeof(char));
                strcpy(heap_buffer, buffer);

                if (!strcmp(buffer_answer, "да"))
                {
                    treeInsertOnLeft(akinator->akinator_tree, heap_buffer);
                    treeMoveToLeftNode(akinator->akinator_tree);
                }

                if (!strcmp(buffer_answer, "нет"))
                {
                    treeInsertOnRight(akinator->akinator_tree, heap_buffer);
                    treeMoveToRightNode(akinator->akinator_tree);
                }
            }
            else
            {
                strcpy(buffer_answer, buffer);
            }

            size_t index = 0;
            number_of_close_bracket = 0;
            while (token_2[index] != '\0')
            {
                if (token_2[index] == '}')
                {
                    treeBackToParentNode(akinator->akinator_tree);
                    number_of_close_bracket++;
                }

                index++;
            }
            printf("token_2: %s\n", token_2);

            token_2 = strtok_r(NULL, ":", &savetoken_2);

        }

        if (number_of_close_bracket == 0)
        {
            treeBackToParentNode(akinator->akinator_tree);
        }

        printf("token: %s\n", token);

        token = strtok_r(NULL, ",", &savetoken_1);
    }

    free(data_file);
}


void akinatorSaveDataBaseToJSON(Akinator* akinator, const char* file_name)
{
    assert(akinator  != NULL);
    assert(file_name != NULL);

    FILE* output_file = fopen(file_name, "w");
    if (output_file == NULL)
    {
        return;
    }

    DataOfNode* tree_data = treePreOrderTravers(akinator->akinator_tree);
    size_t size_of_tree = treeNodesQuantity(akinator->akinator_tree);
    int previous_depth = 0;

    for (size_t index = 0; index < size_of_tree; index++)
    {
        if (previous_depth - tree_data[index].depth >= 1)
        {
            printf("prev: %d\n", previous_depth);
            printf("curr: %d\n", tree_data[index].depth);

            for (int i = 0; i < 2 * (previous_depth - tree_data[index].depth); i++)
            {
            fprintf(output_file, "\n");
                for (int j = 0; j <= 2 * tree_data[index].depth - 2 - i; j++)
                {
                    fprintf(output_file, "\t");
                }
                fprintf(output_file, "}");
            }

            fprintf(output_file, ",");
        }

        if (previous_depth == tree_data[index].depth)
        {
            fprintf(output_file, ",");
        }

        char tabular_buffer[SIZE_OF_BUFFER] = {};

        for (int i = 0; i < 2 * tree_data[index].depth - 2; i++)
        {
            tabular_buffer[i] = '\t';
            tabular_buffer[i + 1] = '\0';
        }

        if (tree_data[index].parent_branch == OnWhatBranch_LEFT)
        {
            fprintf(output_file, "\n%s\"да\":", tabular_buffer);
        }

        if (tree_data[index].parent_branch == OnWhatBranch_RIGHT)
        {
            fprintf(output_file, "\n%s\"нет\":", tabular_buffer);
        }

        if (!tree_data[index].is_end)
        {
            if (tree_data[index].parent_branch != OnWhatBranch_NONE)
            {
                fprintf(output_file, "\n");
            }

            fprintf(output_file, "%s{\n", tabular_buffer);
            fprintf(output_file, "%s\t", tabular_buffer);
            fprintf(output_file, "\"%s\":\n", tree_data[index].data);
            fprintf(output_file, "\t%s{", tabular_buffer);
        }
        else
        {
            fprintf(output_file, " \"%s\"", tree_data[index].data);
        }

        previous_depth = tree_data[index].depth;
    }

    for (int i = 2 * previous_depth - 2; i > 0; i--)
    {
        fprintf(output_file, "\n");
        for (int j = 0; j < i - 1; j++)
        {
            fprintf(output_file, "\t");
        }
        fprintf(output_file, "}");
    }

    free(tree_data);

//     while(!treeIsNodeEnd(akinator->akinator_tree))
//     {
//         fprintf(output_file, "{\n\t\"%s\":\n{", treeGetCurrentNodeData(akinator->akinator_tree));
//         MoveState move_state = treeMoveToLeftNode(akinator->akinator_tree);
//         if (move_state == MoveState_MOVED_TO_NEXT)
//         {
//             fprintf(output_file, "\t\"да\": ");
//             current_depth++;
//         }
//
//         if (move_state == MoveState_EMPTY_NODE)
//         {
//             if(treeIsNodeEnd(akinator->akinator_tree))
//             {
//                 fprintf(output_file, "\"%s\"", treeGetCurrentNodeData(akinator->akinator_tree));
//                 treeBackToParentNode(akinator->akinator_tree);
//             }
//             else
//             {
//                 fprintf(output_file, "\n{\n%s", treeGetCurrentNodeData(akinator->akinator_tree));
//             }
//
//             move_state = treeMoveToRightNode(akinator->akinator_tree);
//             if (move_state == MoveState_MOVED_TO_NEXT)
//             {
//                 printf(",\n");
//                 printf("\t\"нет\": ");
//             }
//         }
//     }

    fclose(output_file);
}


// static --------------------------------------------------------------------------------------------------------------

