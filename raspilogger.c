#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"
#include "dht11.h"

static FILE *LogFileHandle;


void Init(void)
{
  /* Initialize the logger module */
  InitLogger();

  /* Open log file used for logging sensor data */
  LogFileHandle = OpenLogFile("LogData.txt");

  RL_PRINT("Logger initialized\n");

  /* Initialize DHT11 sensors */
  DhtInit();
  RL_PRINT("DHT11 sensors initialized\n");
}

void Exit(void)
{
  RL_PRINT("Closing down log files\n");
  CloseLogFile(LogFileHandle);

  RL_PRINT("Calling logger exit function\n");
  ExitLogger();
}

int main(int argc, char **argv)
{  
  SensorData_t ReturnData;

  /* Initialize raspilogger */
  Init();

  RL_PRINT("Raspilogger initialized\n");

  ReadDht11(&ReturnData, DHT11_SENSOR_1);
  ReadDht11(&ReturnData, DHT11_SENSOR_2);
  //RL_PRINT("ReturnData.TemperatureC=\n", ReturnData.TemperatureC);

  /* Shutdown raspilogger */
  Exit();
  return 0;
}

