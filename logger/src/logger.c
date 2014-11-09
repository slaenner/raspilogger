#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "logger.h"
#include "dht11.h"

FILE *OpenLogFile(char *FileName)
{
  FILE *fp = NULL;

  if((fp = fopen(FileName, "w")) == NULL)
  {
    printf("Failed to open %s\n", FileName);
    exit(1);
  }

  return fp;
}

void CloseLogFile(FILE *handle)
{
  fclose(handle);
}
