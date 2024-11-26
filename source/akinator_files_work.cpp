#include "akinator_files_work.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "helpful_functions.h"
#include "tree.h"


// static --------------------------------------------------------------------------------------------------------------

static const size_t SIZE_OF_BUFFER = 256;

// public --------------------------------------------------------------------------------------------------------------


void akinatorReadDataBaseFromFile(Akinator* akinator, const char* file_path)
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

            token_2 = strtok_r(NULL, ":", &savetoken_2);
        }

        if (number_of_close_bracket == 0)
        {
            treeBackToParentNode(akinator->akinator_tree);
        }

        token = strtok_r(NULL, ",", &savetoken_1);
    }

    free(data_file);
}


// static --------------------------------------------------------------------------------------------------------------



