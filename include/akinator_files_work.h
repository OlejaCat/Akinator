#ifndef AKINATOR_FILES_WORK_H
#define AKINATOR_FILES_WORK_H

#include "akinator_logic.h"

void akinatorReadDataBaseFromJSON(Akinator* akinator, const char* file_path);
void akinatorSaveDataBaseToJSON(Akinator* akinator, const char* file_name);

#endif // AKINATOR_FILES_WORK_H
