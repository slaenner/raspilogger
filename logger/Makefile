CC = gcc
CFLAGS =-I./h -I../dht11/h -Wall
DEPS =
OBJ = src/logger.o ../dht11/src/dht11.c
OBJSIM = ../sim_stubs/src/stubs.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

logger: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

logger_sim: $(OBJ) $(OBJSIM)
	gcc -o ./bin/$@ $^ $(CFLAGS) -I../sim_stubs/h -DSIMULATION
