#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "logger.h"
#include "dht11.h"

int OpenLogFile(char *FileName)
{
  int filedescriptor = 0;

  if ((filedescriptor = open(FileName, O_WRONLY)) < 0)
  {
    printf("Failed to open %s\n", FileName);
    exit(1);
  }

  return filedescriptor;
}

void CloseLogFile(int handle)
{
  close(handle);
}
