#if defined(SIMULATION)

#include <stdio.h>
#include "dht11.h"

#include <time.h>
#include <stdlib.h>



int bcm2835_init(void)
{  
  return 1;
}

unsigned int SimulateSensorCrcResult(void)
{  
  srand48(time(NULL));
  
  if (drand48() > 0.5)
  {
    return DHT11_ERROR;
  }
  else
  {  
    return DHT11_OK;
  }
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
 
  ReturnData.NewData = SimulateSensorCrcResult();

  return &ReturnData;
}

#endif

