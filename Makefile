CC = gcc
CFLAGS =-Ih -Idht11/h -Ilogger/h -Wall
DEPS =
OBJ = logger/src/logger.o dht11/src/dht11.o raspilogger.o

OBJSIM = sim_stubs/src/stubs.o
CFLAGSSIM = -Isim_stubs/h -DSIMULATION

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CFLAGSSIM)

raspberry: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

host: $(OBJ) $(OBJSIM)
	$(CC) -o $@ $^ $(CFLAGS) $(CFLAGSSIM)

clean:
	rm $(OBJ)
