#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>

#include "logger.h"
#include "dht11.h"

static FILE *fpdbg;

void ExitLogger(void)
{
  RL_PRINT("Closing debug log file\n");

  /*Close the log file */
  CloseLogFile(fpdbg);
}


void InitLogger(void)
{
  fpdbg = OpenLogFile("PrgDbgLog.txt");
  RL_PRINT("Logger initialized PrgDbgLog.txt for write\n");
}

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

void PrintDbgLog(const char *func, char *str)
{
  struct timeval time;
  time_t curtime;
  char buf[30];

  /* Get time of day and reformat into buf */
  gettimeofday(&time, NULL);
  curtime = time.tv_sec;
  strftime(buf, 30,"%m-%d-%Y %T",localtime(&curtime));

  /* Write the specified string to the debug log */
  fprintf(fpdbg, "%s %s(): %s", buf, func, str);

  /* Also print it to the screen in simulation mode */
#if defined(SIMULATION)
  printf("%s %s(): %s", buf, func, str);
#endif
}
