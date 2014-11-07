#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"
#include "dht11.h"

static int LogFileHandle = 0;
static char LogFileName[] = "LogData.txt";

void InitLogger()
{
  DhtInit();
  LogFileHandle = OpenLogFile(LogFileName);
}

void ExitLogger()
{
  CloseLogFile(LogFileHandle);
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

