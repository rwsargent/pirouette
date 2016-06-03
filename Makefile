OBJS = pirouette.o socket_layer.o controller.o servo.o connection_manager.o
CC = g++
CFLAGS = -Wall -c -std=c++14 -g
WIRING_FLAGS = -lwiringPi -lpthread
LFLAGS = -Wall -std=c++14
COMP = $(CC) $(DEBUG) $(CFLAGS) $<
EXEC = $(CC) $(LFLAGS) $(WIRING_FLAGS) $(OBJS) -o pirouette

pirouette : $(OBJS)
	$(EXEC)

pirouette.o : pirouette.cpp pirouette.h
	$(COMP)

socket_layer.o: socket_layer.cpp socket_layer.h
	$(COMP)

connection_manager.o: connection_manager.cpp connection_manager.h
	$(COMP)

controller.o: controller.cpp controller.h
	$(COMP)

servo.o: servo.cpp servo.h
	$(COMP)

clean:
	rm -r *.o; rm pirouette

run:
	./pirouette

.PHONY: clean debug

