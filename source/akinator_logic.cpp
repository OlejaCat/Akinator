#include "akinator_logic.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


// static --------------------------------------------------------------------------------------------------------------


typedef enum UserBinaryAnswer
{
    UserBinaryAnswer_ERROR = -1,
    UserBinaryAnswer_NO    =  0,
    UserBinaryAnswer_YES   =  1,
} UserBinaryAnswer;


static const size_t SIZE_OF_BUFFER = 64;

static MoveState akinatorAskQuastion(Akinator* akinator);
static void akinatorAddResult(Akinator* akinator);
static void akinatorAskLastQuastion(Akinator* akinator);
static UserBinaryAnswer processQuastion(void);

static int s_gets(char* str, int n);


// public --------------------------------------------------------------------------------------------------------------


void akinatorQuess(Akinator* akinator)
{
    assert(akinator != NULL);

    if (treeGetCurrentNodeData(akinator->akinator_tree) == NULL)
    {
        printf("Пока ничего нельзя угадать\n");
        akinatorAddResult(akinator);
        return;
    }


    while (!treeIsNodeEnd(akinator->akinator_tree))
    {
        MoveState move_state = akinatorAskQuastion(akinator);
        switch (move_state)
        {
            case MoveState_EMPTY_NODE:
                printf("Неизвестный объект\n");
                akinatorAddResult(akinator);
                return;

            case MoveState_STAYED_INPLACE:
                printf("Выход...\n");
                return;

            default:
                break;
        }
    }

    akinatorAskLastQuastion(akinator);
}


// static --------------------------------------------------------------------------------------------------------------


static MoveState akinatorAskQuastion(Akinator* akinator)
{
    assert(akinator != NULL);

    printf("Этот объект %s?\n", treeGetCurrentNodeData(akinator->akinator_tree));

    switch (processQuastion())
    {
        case UserBinaryAnswer_YES:
            return treeMoveToLeftNode(akinator->akinator_tree);

        case UserBinaryAnswer_NO:
            return treeMoveToRightNode(akinator->akinator_tree);

        default:
            return MoveState_STAYED_INPLACE;
    }
}


static void akinatorAskLastQuastion(Akinator* akinator)
{
    assert(akinator != NULL);

    const char* current_object = treeGetCurrentNodeData(akinator->akinator_tree);
    printf("Загаданный объект %s?\n", current_object);

    char buffer_property[SIZE_OF_BUFFER] = {};
    char buffer_object[SIZE_OF_BUFFER] = {};

    int length_buffer_object = 0;
    int length_buffer_propetry = 0;

    switch (processQuastion())
    {
        case UserBinaryAnswer_YES:
            printf("Объект угадан\n");
            return;

        case UserBinaryAnswer_NO:
            printf("А что вы загадали?\n");
            length_buffer_object = s_gets(buffer_object, SIZE_OF_BUFFER);

            printf("Какое различие <%s> имеет с объектом <%s>\n", buffer_object, current_object);
            length_buffer_propetry = s_gets(buffer_property, SIZE_OF_BUFFER);

            break;

        default:
            return;
    }

    char* property = (char*)calloc((size_t)length_buffer_propetry + 1, sizeof(char));
    memcpy(property, buffer_property, (size_t)length_buffer_propetry);

    char* object = (char*)calloc((size_t)length_buffer_object + 1, sizeof(char));
    memcpy(object, buffer_object, (size_t)length_buffer_object);

    treeInsertOnTopRight(akinator->akinator_tree, property);
    treeBackToParentNode(akinator->akinator_tree);
    treeInsertOnLeft(akinator->akinator_tree, object);
}


static void akinatorAddResult(Akinator* akinator)
{
    assert(akinator != NULL);

    char buffer_object[SIZE_OF_BUFFER] = {};
    printf("Введите объект: ");
    int length_buffer_object = s_gets(buffer_object, SIZE_OF_BUFFER);

    char buffer_property[SIZE_OF_BUFFER] = {};
    printf("Введите отличительное свойство: ");
    int length_buffer_propetry = s_gets(buffer_property, SIZE_OF_BUFFER);

    assert(63 == SIZE_OF_BUFFER - 1);

    if (!buffer_property[0])
    {
        printf("%s:%s", buffer_object, buffer_property);

        printf("Ввод был прерван...\n");
        return;
    }

    char* property = (char*)calloc((size_t)length_buffer_propetry + 1, sizeof(char));
    memcpy(property, buffer_property, (size_t)length_buffer_propetry);

    char* object = (char*)calloc((size_t)length_buffer_object + 1, sizeof(char));
    memcpy(object, buffer_object, (size_t)length_buffer_object);

    treeInsertOnRight(akinator->akinator_tree, property);
    treeMoveToRightNode(akinator->akinator_tree);
    treeInsertOnLeft(akinator->akinator_tree, object);
}


static UserBinaryAnswer processQuastion(void)
{
    char buffer_answer[SIZE_OF_BUFFER] = {};
    s_gets(buffer_answer, SIZE_OF_BUFFER);

    assert(63 == SIZE_OF_BUFFER - 1);

    if (!buffer_answer[0])
    {
        printf("Ввод прерван\n");
        return UserBinaryAnswer_ERROR;
    }

    for (size_t buffer_index = 0; buffer_index < SIZE_OF_BUFFER; buffer_index++)
    {
        buffer_answer[buffer_index] = (char)tolower(buffer_answer[buffer_index]);
    }

    if (!strcmp(buffer_answer, "да"))
    {
        return UserBinaryAnswer_YES;

    }

    if (!strcmp(buffer_answer, "нет"))
    {
        return UserBinaryAnswer_NO;
    }

    printf("Неизвестный ответ...\n");

    return UserBinaryAnswer_ERROR;
}


static int s_gets(char* str, int n)
{
    char* str_read = fgets(str, n, stdin);
    if (!str_read)
        return 0;

    int i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;

    if (str[i] == '\n')
        str[i] = '\0';

    return i;
}
