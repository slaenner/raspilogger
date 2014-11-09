#if !defined(LOGGER_H)
#define LOGGER_H

#include <stdio.h>

FILE *OpenLogFile(char *FileName);
void CloseLogFile(FILE *handle);

#endif
