#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"
#include "dht11.h"

int main(int argc, char **argv)
{  
  printf("Entered main program\n");
  dhtInit();
  dht();
  dht();
  return 0;
}


