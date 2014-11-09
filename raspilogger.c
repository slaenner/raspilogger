#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"
#include "dht11.h"

static FILE *LogFileHandle;
static FILE *PrgDbgLogFileHandle;

void PrintDbgLog(char *str)
{
  
}


void InitLogger()
{
  /* Open log file used for logging sensor data */
  LogFileHandle = OpenLogFile("LogData.txt");
  PrgDbgLogFileHandle = OpenLogFile("PrgDbgLog.txt");
  PrintDbgLog("Opened log files for write\n");

  /* Initialize DHT11 sensors */
  DhtInit();
  PrintDbgLog("Initialized DHT11\n");
}

void ExitLogger()
{
  CloseLogFile(LogFileHandle);
  CloseLogFile(PrgDbgLogFileHandle);
}

int main(int argc, char **argv)
{  
  SensorData_t ReturnData;
  printf("Entered main program\n");
  InitLogger();

  ReadDht11(&ReturnData, DHT11_SENSOR_1);
  printf("ReturnData.TemperatureC=%d\n", ReturnData.TemperatureC);

  ReadDht11(&ReturnData, DHT11_SENSOR_2);
  printf("ReturnData.TemperatureC=%d\n", ReturnData.TemperatureC);

  ExitLogger();
  return 0;
}

