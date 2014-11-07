#if defined(SIMULATION)

#include <stdio.h>
#include "dht11.h"

int bcm2835_init(void)
{  
  return 1;
}

SensorData_t* GetData(int pin)
{  
  static SensorData_t ReturnData;

  if(pin == DHT11_1_Pin)
    ReturnData.TemperatureC = 21;
  else
    ReturnData.TemperatureC = 22;
  ReturnData.RHPercent = 75;
  ReturnData.DevPointC = DewPoint((double)ReturnData.TemperatureC, (double)ReturnData.RHPercent);
  ReturnData.NewData = DHT11_OK;

  return &ReturnData;
}

#endif

