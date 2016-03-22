OBJS = pirouette.o socket_layer.o controller.o
CC = g++
DEBUG  = -g
CFLAGS = -Wall -c -std=c++14
WIRING_FLAGS = -lwiringPi -lpthread
LFLAGS = -Wall -std=c++14

pirouette : $(OBJS)
	$(CC) $(LFLAGS) $(WIRING_FLAGS) $(OBJS) -o pirouette

pirouette.o : pirouette.cpp pirouette.h
	$(CC) $(CFLAGS) pirouette.cpp

socket_layer.o: socket_layer.cpp socket_layer.h
	$(CC) $(CFLAGS) socket_layer.cpp

controller.o: controller.cpp controller.h
	$(CC) $(CFLAGS) $(WIRING_FLAGS) controller.cpp

clean:
	rm -r *.o *~; rm pirouette

run:
	./pirouette
