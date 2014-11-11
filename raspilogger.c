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

  /* Initialize DHT11 sensors */
  DhtInit();

  /* Trace */
  RL_PRINT("Raspilogger Init() completed\n");
}

void Exit(void)
{
  /* Trace before log files are closed */
  RL_PRINT("Raspilogger Exit() called\n");

  /* Close down log files and call logger exit function */
  CloseLogFile(LogFileHandle);
  ExitLogger();
}

void ReadSensor(SensorData_t * ReturnData, int SensorId)
{
  char buf[100];
  sprintf(buf, "Reading from DHT11 Sensor %d\n", SensorId);
  RL_PRINT(buf);

  /* Invalidate sensor return code */
  ReturnData->NewData = DHT11_ERROR;

  /* Read sensor until result has been received successfull */
  while(ReturnData->NewData != DHT11_OK)
  {
    RL_PRINT("Fetching data from DHT11\n");

    /* Read DHT11 sensor 2 */
    ReadDht11(ReturnData, SensorId);

    if(ReturnData->NewData == DHT11_OK)
    {
      RL_PRINT("Data from DHT11 read OK\n");
    }
    else
    {
      RL_PRINT("Data from DHT11 ERROR - Retrying\n");
    }
  }  
}


int main(int argc, char **argv)
{
  SensorData_t ReturnData;

  /* Initialize raspilogger */
  Init();

  /* Trace */
  RL_PRINT("Raspilogger initialized\n");

  RL_PRINT("Reading data from DHT11 Sensor 1\n");
  ReadSensor(&ReturnData, DHT11_SENSOR_1);

  RL_PRINT("Storing data from DHT11 Sensor 1\n");
  LogSensorData(LogFileHandle, &ReturnData, DHT11_SENSOR_1);

  RL_PRINT("Reading data from DHT11 Sensor 2\n");
  ReadSensor(&ReturnData, DHT11_SENSOR_2);

  RL_PRINT("Storing data from DHT11 Sensor 2\n");
  LogSensorData(LogFileHandle, &ReturnData, DHT11_SENSOR_2);

  /* Shutdown raspilogger */
  Exit();
  return 0;
}

